#ifndef FUTURE_H
#define FUTURE_H

#include <iostream>
#include <mutex>
#include <atomic>

template<typename T>
class Future {
    private:
        std::atomic<bool> done;
        T res;
    public:
        Future(  ) {
            res = T();
            // std::cout << "Future ctor" << std::endl;
            done = false;
        }

        T resolve(  ) {
            // std::cout << done << std::endl;
            if( done ) {
                // std::cout << "if" << std::endl;
                return res;
            } else {
                return T();
            }

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
};

#endif
