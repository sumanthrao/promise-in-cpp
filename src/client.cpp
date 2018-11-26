#include <iostream>

using namespace std;

#include "../include/proxy.h"

int main( int argc, char const *argv[] ) {
    
    Proxy handle;

    Future<int> f1 = handle.task1(  );
    // Future<float> f2 = handle.task2(  );
    // Future<char> f3 = handle.task3(  );

    cout << "Task 1 : " << f1.resolve() << endl;
    // cout << "Task 2 : " << f2.resolve() << endl;
    // cout << "Task 3 : " << f3.resolve() << endl; 


    return 0;
}
