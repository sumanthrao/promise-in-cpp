#include "../include/task.h"
#include <unistd.h>

using namespace std::chrono;

int
Task1::call(  ) {
	// start the task
	auto start = high_resolution_clock::now();
    DEBUG("Task-1  executing... \n");
	sleep(2);
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 
	// end the task
    cout << "Time taken by Task-1: "<< duration.count() << " milliseconds" << endl; 
	return 1;
}


string
Task2::call(  ) {
	// start the task
	auto start = high_resolution_clock::now();
    DEBUG("Task-2 executing... \n");
	sleep(3);
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 
	// end the task
    cout << "Time taken by Task-2: "<< duration.count() << " milliseconds" << endl; 
	return "I rock!!";
}

char
Task3::call(  ) {
	// start the task
	auto start = high_resolution_clock::now();
    DEBUG("Task-3 executing... \n");
	sleep(4);
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 
	// end the task
    cout << "Time taken by Task-3: "<< duration.count() << " milliseconds" << endl; 
	return 'a';
}
