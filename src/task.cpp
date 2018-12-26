#include "../include/task.h"
#include <unistd.h>
#include <thread>
using namespace std::chrono;

int
Task1::call(  ) {
	// start the task
	auto start = high_resolution_clock::now();
    DEBUG("Task-1 executing... \n");
	sleep(2);
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start); 
	// end the task
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n" << "Task 1: " << std::this_thread::get_id() << "\n" << "Time: " << duration.count() << " milliseconds" << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;  
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
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n" << "Task 2: " << std::this_thread::get_id() << "\n" << "Time: " << duration.count() << " milliseconds" << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
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

    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << "\n" << "Task 3: " << std::this_thread::get_id() << "\n" << "Time: " << duration.count() << " milliseconds" << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl; 
	return 'a';
}


int
Task4::call(  ) {
	return func();
}
