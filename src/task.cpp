#include "task.h"

int
Task1::call(){
	DEBUG("Task1 called");
	return 1;
}


float
Task2::call(){
	DEBUG("Task2 called");
	return 1.0;
}

char
Task3::call(){
	DEBUG("Task3 called");
	return 'a';
}