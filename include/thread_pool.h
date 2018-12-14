#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

#include "pool_queue.h"

class ThreadPool {
    private:
        class ThreadWorker {
            private:
                int m_id;
                ThreadPool *m_pool;

            public:
                ThreadWorker( ThreadPool *pool, const int id): m_pool( pool ), m_id( id ) {
                }

                void operator(  )(  ) {
                    /*
                        Info
                    */

                    std::cout << "Thread pool: \t\tthread: " << std::this_thread::get_id() << " added" << endl;

                    std::function< void(  ) > func;
                    bool dequeued;
                    while (!m_pool->m_shutdown) {
                        {
                            std::unique_lock<std::mutex> lock( m_pool->m_conditional_mutex );
                            if ( m_pool->m_queue.empty(  ) ) {
                                m_pool->m_conditional_lock.wait( lock );
                            }
                            dequeued = m_pool->m_queue.dequeue( func );
                        }
                        if ( dequeued ) {
                            // std::thread::id this_id = std::this_thread::get_id();
                            // std::cout << "thread id is" << this_id << endl;
                            {   
                                /*
                                */
                                std::unique_lock<std::mutex> active_lock( m_pool->m_active_mutex );
                                
                                if( ++( m_pool->active_threads ) == m_pool->m_threads.size() ){

                                    DEBUG("********************************************************************");
                                    DEBUG("Growing the pool");
                                    DEBUG("********************************************************************");


                                    int old_size = m_pool->m_threads.size();
                                    
                                    /*
                                        Info
                                    */                                    
                                    cout << "Thread Pool: \t\tPool size doubled --- New Pool size = " << old_size * 2 << std::endl;

                                    for(int i = old_size; i < (old_size * 2) ; ++i) {
                                        m_pool->add_to_pool();
                                    }
                                    DEBUG("New thread pool size - ");
                                    DEBUG(m_pool->m_threads.size());
                                }
                            }
                            func(  );
                            {
                                std::unique_lock<std::mutex> active_lock( m_pool->m_active_mutex );  
                                --( m_pool->active_threads );                                                                                              
                            }
                        }
                    }
                }
        };

        bool m_shutdown;
        SafeQueue<std::function<void()>> m_queue;
        int active_threads = 0;
        std::mutex m_active_mutex;
        std::vector<std::thread> m_threads;
        std::mutex m_conditional_mutex;
        std::condition_variable m_conditional_lock;
    
    public:
        ThreadPool( const int n_threads ): m_threads( std::vector<std::thread>(n_threads) ), m_shutdown( false ) {
        }

        ThreadPool( const ThreadPool & ) = delete;
        ThreadPool( ThreadPool && ) = delete;

        ThreadPool& operator=( const ThreadPool & ) = delete;
        ThreadPool& operator=( ThreadPool && ) = delete;


        ThreadWorker create_new_thread_worker( int index ) {
            return ThreadWorker(this, index);
        }

        // Inits thread pool
        void init(  ) {
            cout << "Thread Pool: \t\tInitialisation" << std::endl;
            for (int i = 0; i < m_threads.size(); ++i) {
                m_threads[i] = std::thread(ThreadWorker(this, i));
            }
        }

        // Waits until threads finish their current task and shutdowns the pool
        void shutdown(  ) {
            m_shutdown = true;
            m_conditional_lock.notify_all();
            
            for (int i = 0; i < m_threads.size(  ); ++i) {
                if(m_threads[i].joinable(  )) {
                    m_threads[i].join(  );
                }
            }

            cout << "Thread Pool: \t\tShut down" << std::endl;

        }

        void add_to_pool(  ) {
            DEBUG("new thread added to pool");
            m_threads.push_back(std::thread(ThreadWorker(this, m_threads.size() + 1)));
        }

        // Submit a function to be executed asynchronously by the pool
        template<typename F, typename...Args>
        auto submit( F&& f, Args&&... args ) -> std::future< decltype( f( args... ) ) > {
            // Create a function with bounded parameters ready to execute
            std::function< decltype( f( args... ) )(  ) > func = std::bind( std::forward< F >( f ), std::forward< Args >( args )... );
            
            // Encapsulate it into a shared ptr in order to be able to copy construct / assign 
            auto task_ptr = std::make_shared< std::packaged_task< decltype( f( args... ) )(  ) > >( func );

            // Wrap packaged task into void function
            std::function<void()> wrapper_func = [ task_ptr ](  ) { ( *task_ptr )(  ); };

            {
                std::unique_lock<std::mutex> lock( m_conditional_mutex );
                // Enqueue generic wrapper function
                m_queue.enqueue( wrapper_func );
                // Wake up one thread if its waiting
                m_conditional_lock.notify_one(  );
            }
            
            // Return future from promise
            return task_ptr->get_future(  );
        }
};

#endif