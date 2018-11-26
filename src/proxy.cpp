#include "../include/proxy.h"

Future<int>*
Proxy::task1(  ) {
    // make a callback and push that to the queue and return the callback
    Future<int> *f = new Future<int>();

    Task1 *t = new Task1( f );

    scheduler.enqueue<int>( t );

    return f;

}

Future<string>*
Proxy::task2(  ) {
    // make a callback and push that to the queue and return the callback

    Future<string> *f = new Future<string>();

    Task2 *t = new Task2( f );

    scheduler.enqueue<string>( t );

    return f;
}

Future<char>*
Proxy::task3(  ) {
    // make a callback and push that to the queue and return the callback

    Future<char> *f = new Future<char>();

    Task3 *t = new Task3( f );

    scheduler.enqueue<char>( t );

    return f;
}
