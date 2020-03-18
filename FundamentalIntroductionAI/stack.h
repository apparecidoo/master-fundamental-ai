#include <iostream>

#ifndef STACK_H
#define STACK_H

#define SIZE 100

using namespace std;

class Stack {
public:
	Stack();
	~Stack();

	void push(int value); // insert a value in the stack
	int pop(); // remove the last value in the stack
	void print(); // print all values from stack
	void test(); // method to test

private:
	int top; // position of last insertion
	int values[SIZE]; // array of values
	
	bool isEmpty(); // check if the stack is empty
	bool is_full(); // check if the stack is full
};

#endif
