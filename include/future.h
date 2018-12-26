#ifndef FUTURE_H
#define FUTURE_H

#include <iostream>
#include <mutex>
#include <atomic>
#include <unistd.h>
#include <thread>
#include <condition_variable>

template<typename T>
class Future {
    private:
        std::atomic<bool> done;
        T res;
        std::condition_variable my_cond;
        std::mutex my_mutex;
    public:
        Future(  ) {
            res = T();
            // std::cout << "Future ctor" << std::endl;
            done = false;
        }

        T resolve(  ) {
            // std::cout << done << std::endl;
            
            while( !done ) {
                std::unique_lock<std::mutex> lk(my_mutex);
                my_cond.wait(lk);
                //sleep(3);
            }
            return res;
        

            // return res;
        }

        bool is_available(  ) {
            return done;
        }

        void set( T res ) {
            // std::cout << "Future set!\n";
            //std::cout << res << "h"; 
            this->res = res;
            //this->res = 500;
            done = true;
        }

        void release(  ) {
            my_cond.notify_one();
        }
};

#endif
