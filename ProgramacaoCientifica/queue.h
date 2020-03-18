#include <iostream>

#ifndef QUEUE_H
#define QUEUE_H

#define SIZE 100

using namespace std;

class Queue {
public:
	Queue();
	~Queue();

	void enqueue(int value); // insert a value in the queue
	int dequeue(); // remove the last value in the queue
	void print(); // print all values from queue
	void test(); // method to test

private:
	int first_position; // first position of queue to be retired
	int last_position; // last position of queue, last value arrived
	int values[SIZE]; // array of values
	int number_values; // number of values in the queue

	bool isEmpty(); // check if the stack is empty
	bool is_full(); // check if the stack is full
	void addQueue(); // add position analysing a circular queue, using mod %
	void subQueue(); // subtract position analysing a circular queue, using mod %

};

#endif
