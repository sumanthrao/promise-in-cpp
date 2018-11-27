#include <iostream>
#include <unistd.h>
#include <random>
#include <thread>
using namespace std;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);


void simulate_hard_computation() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

#include "../include/proxy.h"

int main( int argc, char const *argv[] ) {

    Proxy handle;

    
    Future<int> *f1 = handle.task1(  );
    Future<string> *f2 = handle.task2(  );
    Future<char> *f3 = handle.task3(  );
    
    // Do some other work
    //sleep(2);

    simulate_hard_computation();

    int ans = f1->resolve();
    cout << "Task 1 : " << ans << endl;

    // Do some other work
    
    cout << "Task 2 : " << f2->resolve() << endl;

    // Do some other work
    //sleep(2);
    cout << "Task 3 : " << f3->resolve() << endl;

    
    return 0;
}
