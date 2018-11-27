#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include "shared_queue.h"
#include "../include/thread_pool.h"
#include <thread>

typedef std::function<void()> Callback;

class Scheduler {
    private:
        Scheduler( const Scheduler& ) = delete;
        Scheduler& operator=( const Scheduler& ) = delete;
        shared_queue<Callback> mq_;
        std::thread thd_;
        bool done_;
        int num_threads;
        ThreadPool *pool_;
        Callback quit_token;
        //int end_;
    public:
        Scheduler( int num_threads );

        template<typename T>
        void enqueue( Task<T> *t ) {
            mq_.push( [ t ](  ) mutable { t->set_result( t-> call(  ) ); } );
        }

        void dispatch (  );

        void doDone(  );

        ~Scheduler(  );
};

#endif
