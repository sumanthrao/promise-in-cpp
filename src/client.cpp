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


    Proxy *handle = new Proxy();
    cout << "Client: \t\tregistering task 1" << std::endl;
    Future<int> *f1 = handle->task1(  );
    cout << "Client: \t\tregistering task 2" << std::endl;
    Future<string> *f2 = handle->task2(  );
    cout << "Client: \t\tregistering task 3" << std::endl;
    Future<char> *f3 = handle->task3(  );
    

    // Do some other work
    //sleep(2);
    
    simulate_hard_computation();
    simulate_hard_computation();
    simulate_hard_computation();


    // int f1_ans = f1->resolve();
    // while(f1_ans == 0)
    //   f1_ans = f1->resolve();
    // cout << "Task 1 : " << f1_ans << endl;

    // // Do some other work
    
    // string f2_ans = f2->resolve();
    // while(f2_ans.compare("") == 0)
    //   f2_ans = f2->resolve();

    // cout << "Task 2 : " << f2_ans << endl;

    // // Do some other work
    // //sleep(2);
    // char f3_ans = f3->resolve();
    // while(f3_ans == '\0')
    //   f3_ans = f3->resolve();
    // cout << "Task 3 : " << f3->resolve() << endl;

    int future_count = 0;
    while( future_count < 1 ) {
      int f1_ans = f1->resolve();
      string f2_ans = f2->resolve();
      char f3_ans = f3->resolve();

      if( f2_ans.compare("") != 0 ){
        f2_ans = f2->resolve();
        cout << "Client: \t\tresult of task 2: " << f2_ans <<  std::endl;
        cout << "Client: \t\tregistering task 2" << std::endl;
        f2 = handle->task2(); 
        future_count++;
      }
      if( f1_ans != 0 ){
        f1_ans = f1->resolve();
        cout << "Client: \t\tresult of task 1: " << f1_ans << std::endl;
        cout << "Client: \t\tregistering task 1" << std::endl;
        f1 = handle->task1();
        future_count++; 
      }
      if( f3_ans != '\0' ){
        f3_ans = f3->resolve();
        cout << "Client: \t\tresult of task 3: " << f3_ans << std::endl;
        cout << "Client: \t\tregistering task 3" << std::endl;
        f3 = handle->task3();
        future_count++;
      }
    }

    int f1_ans = f1->resolve();
    string f2_ans = f2->resolve();
    char f3_ans = f3->resolve();

    while( f2_ans.compare("") != 0 ){
      f2_ans = f2->resolve();
      cout << "Client: \t\tresult of task 2: " << f2_ans <<  std::endl;
      f2_ans = f2->resolve();
    }
    while( f1_ans != 0 ){
      f1_ans = f1->resolve();
      cout << "Client: \t\tresult of task 1: " << f1_ans << std::endl;
      f1_ans = f1->resolve();
    }
    while( f3_ans != '\0' ){
      f3_ans = f3->resolve();
      cout << "Client: \t\tresult of task 3: " << f3_ans << std::endl;
      f3_ans = f3->resolve();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 

    delete handle;  

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n" << "Program Execution Time: " << duration.count() << " milliseconds" << "\n" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
  
    return 0;
}
