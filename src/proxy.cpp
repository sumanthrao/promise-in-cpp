#include "../include/proxy.h"

Future<int>
Proxy::task1(  ) {
    // make a callback and push that to the queue and return the callback
    Future<int> f;

    Task1 t( f );
    
    scheduler.enqueue<int>( &t );

    return f;

}

Future<float>
Proxy::task2(  ) {
    // make a callback and push that to the queue and return the callback

    Future<float> f;

    Task2 t( f );
    
    scheduler.enqueue<float>( &t );    

    return f;
}

Future<char> 
Proxy::task3(  ) {
    // make a callback and push that to the queue and return the callback

    Future<char> f;

    Task3 t( f );
    
    scheduler.enqueue<char>( &t );

    return f;
}