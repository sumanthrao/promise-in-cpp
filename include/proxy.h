#ifndef PROXY_H
#define PROXY_H

#include "future.h"
#include "scheduler.h"
#include "task.h"

class Proxy {
    private:
        Scheduler scheduler;

    public:
        Future<int>* task1(  );

        Future<string>* task2(  );

        Future<char>* task3(  );
};


#endif
