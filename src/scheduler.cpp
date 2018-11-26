#include "../include/scheduler.h"

Scheduler::Scheduler(  ) {
    thd_ = std::thread(&Scheduler::dispatch, this);
}

void
Scheduler::doDone(  ) {
    done_ = true;
}

void
Scheduler::dispatch(  ) {
    while(!done_) {
        Callback func;
        mq_.wait_and_pop(func);
        func();
    }

}

Scheduler::~Scheduler(  ) {
    Callback quit_token = std::bind(&Scheduler::doDone, this);
    mq_.push(quit_token); // tell thread to exit

    thd_.join();
} 