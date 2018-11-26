#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "future.h"
#include "task.h"
#include "shared_queue.h"

typedef std::function<void()> Callback;

class Scheduler {
    private:
        Scheduler( const Scheduler& ) = delete;
        Scheduler& operator=( const Scheduler& ) = delete;
        shared_queue<Callback> mq_;

    public:

        Scheduler(  ) {
            dispatch();
        }

        template<typename T>
        void enqueue(Task<T> *t) {
            mq_.push( []() { t->set_result( t->call(  ) ) } );
        } 


        void dispatch () {
            
        }
};

#endif