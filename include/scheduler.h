#ifndef SCHEDULER_H
#define SCHEDULER_H

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
        bool done_;

    public:
        Scheduler(  );

        template<typename T>
        void enqueue( Task<T> *t ) {
            mq_.push( [ t ](  ) mutable { DEBUG("lambda"); t->set_result( 500 ); } );
        } 

        void dispatch (  );

        void doDone(  ); 

        ~Scheduler(  );
};

#endif