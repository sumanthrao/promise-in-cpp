#ifndef PROXY_H
#define PROXY_H

#include "future.h"
#include "scheduler.h"
#include "task.h"

#define THREADS 2

class Proxy {
    private:
        Scheduler *scheduler;

    public:

        Proxy(  ) {
            scheduler = new Scheduler(THREADS);
        }

        ~Proxy(  ) {
            delete scheduler;
        }

        Future<int>* task1(  );

        Future<string>* task2(  );

        Future<char>* task3(  );
};


#endif
