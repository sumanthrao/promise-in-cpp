#ifndef FUTURE_H
#define FUTURE_H

template<typename T>
class Future {
    private:
        bool done;
        T res;
    public:
        Future(  ) {
            res = T();
        }

        T resolve(  ) {
            if( done ) {
                return res;
            } else {
                // force scheduler to schedule method corresponding to this promise
            }
        } 

        bool is_available(  ) {
            return done;
        }

        void set( T res ) {
            this->res = res;
            done = true;
        }
};

#endif