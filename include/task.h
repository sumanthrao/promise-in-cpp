#ifndef TASK_H
#define TASK_H

#include <iostream>

#include "future.h"
#include <typeinfo>

using namespace std;



#define DEBUG(x) do { \
cerr << "DBG:"<< x << ": " << std::endl;\
}	 while (0);

template<typename T>
class Task {
	private:
		Future<T> *future_instance;
	public:
		Task( Future<T> *f ): future_instance( f ) {  };
		virtual T call(  ) = 0;
		void set_result( T res ) {
			// DEBUG("set_result: ");
			// const std::type_info& ti1 = typeid(res);
			// std::cout << typeid(res).name() << "\n";// it works only for strings da....
			// cout << res << "\n";
			future_instance->set( res );
		}
};

class Task1: public Task<int> {
	public:
		Task1(Future<int> *f): Task( f ) {  };
		virtual int call(  );
};

class Task2: public Task<string> {
	public:
        Task2( Future<string> *f ): Task( f ) {  };
		virtual string call(  );
};


class Task3: public Task<char>{
	public:
        Task3( Future<char> *f): Task( f ) {  };
		virtual char call(  );
};

#endif
