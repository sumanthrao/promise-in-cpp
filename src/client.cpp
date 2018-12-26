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

Proxy *handle = new Proxy();

int func1( int a ) {
  return a * a;
}

int func2( int a, int b ) {
  return a + b;
}

int func3( std::function<int()> f1, std::function<int()> f2) {
  Future<int> *fut1 = handle->task(f1);
  Future<int> *fut2 = handle->task(f2);

  int res1 = fut1->resolve();
  int res2 = fut2->resolve();
  

  return res1 + res2;

}

template<typename F, typename...Args>
auto submit_task( F&& f, Args&&... args ) -> std::function<int( )> {
    // Create a function with bounded parameters ready to execute
    std::function< decltype( f( args... ) )(  ) > func = std::bind( std::forward< F >( f ), std::forward< Args >( args )... );
    
    // Encapsulate it into a shared ptr in order to be able to copy construct / assign 
    auto task_ptr = std::make_shared< std::packaged_task< decltype( f( args... ) )(  ) > >( func );

    // Wrap packaged task into void function
    std::function<int()> wrapper_func = [ task_ptr ](  ) { ( *task_ptr )(  ); };

    return wrapper_func;
}


int main( int argc, char const *argv[] ) {

    DEBUG("Program started executing...");
    auto start = high_resolution_clock::now();
    
    cout << "Client: \t\tregistering task 1" << std::endl;
    Future<int> *f1 = handle->task1(  );
    cout << "Client: \t\tregistering task 2" << std::endl;
    Future<string> *f2 = handle->task2(  );
    cout << "Client: \t\tregistering task 3" << std::endl;
    Future<char> *f3 = handle->task3(  );
    
    int arg1 = 10;
    int arg2 = 20;
    int arg3 = 30;
    
    Future<int> *f4 = handle->task([arg1](  ){ return func1( arg1 ); });
    sleep(2);
    cout << "\n\nfunc1( " << arg1 << " ) = " << f4->resolve() << "\n" << endl;

    f4 = handle->task([arg2, arg3](  ){ return func2( arg2,  arg3); });
    sleep(2);
    cout << "\n\nfunc2( " << arg2 << ", " << arg3 << " ) = " << f4->resolve() << "\n" <<  endl;

    f4 = handle->task([arg1, arg2, arg3](  ){ return func3([arg1](  ){ return func1( arg1 ); }, [arg2, arg3](  ){ return func2( arg2,  arg3); }); });
    sleep(2);

    cout << "\n\nfunc3( func1 ( " << arg1 << " ), func2( " << arg2 << ", " << arg3 << " ) ) = " << f4->resolve() << "\n" << endl;

    // Do some other work
    //sleep(2);
    
    simulate_hard_computation();
    simulate_hard_computation();
    simulate_hard_computation();
    
    cout << "\nResult of task 1: " << f1->resolve() << endl;

    cout << "\nResult of task 2: " << f2->resolve() << endl;

    cout << "\nResult of task 3: " << f3->resolve() << "\n" << endl;


    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 

    delete handle;  

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n" << "Program Execution Time: " << duration.count() << " milliseconds" << "\n" << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
  
    return 0;
}
