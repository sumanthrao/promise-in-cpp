#include <iostream>
#include <unistd.h>
using namespace std;


#include "../include/proxy.h"

int main( int argc, char const *argv[] ) {

    Proxy handle;

    
    Future<int> *f1 = handle.task1(  );
    Future<string> *f2 = handle.task2(  );
    Future<char> *f3 = handle.task3(  );
    
    // Do some other work
    //sleep(2);
    int ans = f1->resolve();
    cout << "Task 1 : " << ans << endl;

    // Do some other work
    sleep(2);
    cout << "Task 2 : " << f2->resolve() << endl;

    // Do some other work
    //sleep(2);
    cout << "Task 3 : " << f3->resolve() << endl;

    
    return 0;
}
