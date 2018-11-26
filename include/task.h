#ifndef TASK_H
#define TASK_H

#include <iostream> 

#include "future.h"

using namespace std;



#define DEBUG(x) do { \ 
cerr << #x << ": " << std::endl;\
}	 while (0);

template<typename T> 
class Task {
	private:
		Future<T> future_instance;
	public:
		Task( Future<T> f ): future_instance( f ) {  }; 
		virtual T call(  ) = 0;
		void set_result( T res ) {
			future_instance.set( res );
		}
};

class Task1: public Task<int> {
	public:
		Task1(Future<int> f): Task( f ) {  };
		int call(  );
};

class Task2: public Task<float> {
	public:
        Task2( Future<float> f ): Task( f ) {  }; 
		float call(  );
};


class Task3: public Task<char>{
	public:
        Task3( Future<char> f): Task( f ) {  };  
		char call(  );	
};

#endif


