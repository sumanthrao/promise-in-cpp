#include "../include/scheduler.h"

Scheduler::Scheduler(  ) {
    std::cout << "Scheduler ctor" << std::endl;
    done_ = false;
    // std::thread::id this_id = std::this_thread::get_id();
    // std::cout << "thread id is" << this_id << endl;
    thd_ = std::thread(&Scheduler::dispatch, this);
}

void
Scheduler::doDone(  ) {
    done_ = true;
}

void
Scheduler::dispatch(  ) {
    // std::cout << "dispatch()" << std::endl;
    // std::thread::id this_id = std::this_thread::get_id();
    // std::cout << "thread id is" << this_id << endl;
    while(!done_) {
        // std::cout << "dispatch()" << std::endl;
        // std::thread::id this_id = std::this_thread::get_id();
        // std::cout << "thread id is" << this_id << endl;
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