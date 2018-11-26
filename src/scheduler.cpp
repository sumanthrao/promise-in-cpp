#include "../include/scheduler.h"
#include <unistd.h>
Scheduler::Scheduler(  ) {
    //std::cout << "Scheduler ctor" << std::endl;
    done_ = false;
    // std::thread::id this_id = std::this_thread::get_id();
    // std::cout << "thread id is " << this_id << endl;
    thd_ = std::thread(&Scheduler::dispatch, this);
}

void
Scheduler::doDone(  ) {
    //std::cout << "doDone is called" << std::endl; 
    done_ = true; 
}

void
Scheduler::dispatch(  ) {
    
    // std::cout << "dispatch()" << std::endl;
    // std::cout << "done_ = " << done_ << std::endl;
    // std::thread::id this_id = std::this_thread::get_id();
    // std::cout << "thread id is" << this_id << endl;
    //sleep(2);
    while(!this->done_) {
        // std::cout << "dispatch()" << std::endl;
        // std::thread::id this_id = std::this_thread::get_id();
        // std::cout << "thread id is" << this_id << endl;
        if( (this->mq_).empty(  ) ) {
            // std::cout << "here" << std::endl;
            continue;
        }
        Callback func;
        (this->mq_).wait_and_pop(func);
        func();
    }

}

Scheduler::~Scheduler(  ) {
    //cout << "4" << endl;
    Callback quit_token = std::bind(&Scheduler::doDone, this);
    mq_.push(quit_token); // tell thread to exit
    //std::cout<<"quit token pushed"<<std::endl;
    // std::thread::id this_id = std::this_thread::get_id();
    // std::cout << "thread id is" << this_id << endl;
    // std::cout<< thd_.joinable() <<std::endl;
    // thd_.detach();
    thd_.join();
    // std::cout<<"thd joined"<<std::endl;
} 
