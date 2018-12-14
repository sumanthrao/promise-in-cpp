#include "../include/scheduler.h"
#include <unistd.h>

Scheduler::Scheduler( int num_threads ): num_threads( num_threads ) {
    cout << "Scheduler: \t\tStarted!" << std::endl;
    done_ = false;
    pool_ = new ThreadPool( num_threads );
    pool_ -> init();
    quit_token = std::bind(&Scheduler::doDone, this);
    thd_ = std::thread(&Scheduler::dispatch, this);
}

void
Scheduler::doDone(  ) {
    done_ = true; 
}

void
Scheduler::dispatch(  ) {
    
    while(!this->done_) {
        if( (this->mq_).empty(  ) ) {
            continue;
        }
        Callback func;
        (this->mq_).wait_and_pop(func);
        cout << "Scheduler: \t\tsubmits a task to the pool" << std::endl;
        pool_->submit(func);
    }

}

Scheduler::~Scheduler(  ) {
    //cout << "4" << endl;
    mq_.push(quit_token); 
    thd_.join();
    pool_->shutdown();
    cout << "Sheduler: \t\tShut down" << std::endl;
    // std::cout<<"thd joined"<<std::endl;
} 
