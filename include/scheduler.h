#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "future.h"
#include "task.h"
#include "shared_queue.h"
#include <thread>

typedef std::function<void()> Callback;

class Scheduler {
    private:
        Scheduler( const Scheduler& ) = delete;
        Scheduler& operator=( const Scheduler& ) = delete;
        shared_queue<Callback> mq_;
        std::thread thd_;

    public:

        Scheduler(  ) {
            thd_ = std::thread(&Scheduler::dispatch, this);
        }

        template<typename T>
        void enqueue( Task<T> *t ) {
            mq_.push( [  ](  ) { t->set_result( t->call(  ) ) } );
        } 


        void dispatch (  ) {
            Callback func;
            mq_.wait_and_pop(func);
            func();
        }

        ~Scheduler(  ) {
            thd_.join();
        } 
};

#endif