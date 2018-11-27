#include <iostream>
#include <unistd.h>
#include <random>
#include <thread>
using namespace std;
using namespace std::chrono;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);


void simulate_hard_computation() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

#include "../include/proxy.h"

int main( int argc, char const *argv[] ) {

    DEBUG("Program started executing...");
    auto start = high_resolution_clock::now();


    Proxy handle;

    Future<int> *f1 = handle.task1(  );
    Future<string> *f2 = handle.task2(  );
    Future<char> *f3 = handle.task3(  );
    
    // Do some other work
    //sleep(2);
    
    simulate_hard_computation();
    


    int f1_ans = f1->resolve();
    while(f1_ans == 0)
      f1_ans = f1->resolve();
    cout << "Task 1 : " << f1_ans << endl;

    // Do some other work
    
    string f2_ans = f2->resolve();
    while(f2_ans.compare("") == 0)
      f2_ans = f2->resolve();

    cout << "Task 2 : " << f2_ans << endl;

    // Do some other work
    //sleep(2);
    char f3_ans = f3->resolve();
    while(f3_ans == '\0')
      f3_ans = f3->resolve();
    cout << "Task 3 : " << f3->resolve() << endl;

    
	  
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << "Time taken by the program: "<< duration.count() << " milliseconds" << endl; 
	
    return 0;
}
