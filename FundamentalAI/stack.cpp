#include "pch.h"
#include "stack.h"

Stack::Stack()
{
	top = 0;
}

Stack::~Stack()
{
	top = 0;
}

void Stack::push(int value)
{
	if (!is_full()) {
		values[top] = value;
		top++;

		cout << endl << "Push number: " << value << endl;
	}
	else {
		cout << endl << "**The stack is full." << endl;
	}
}

int Stack::pop()
{
	int value = -1; // return -1 if something is wrong

	if (!isEmpty()) {
		value = values[top - 1];
		top--;

		cout << endl << "Pop number: " << value << endl;
	}
	else {
		cout << endl << "**The stack is empty." << endl;
	}

	return value;
}

void Stack::print()
{
	cout << endl << "Values from Stack: " << endl;
	cout << "[down] - ";

	// sweeping the array to print in the screen
	for (int i = 0; i < top; i++)
	{
		cout << values[i] << " | ";
	}

	cout << " - [top]";

	cout << endl;
}

void Stack::test()
{
	this->push(10);
	this->print();
	this->push(9);
	this->print();
	this->push(8);
	this->pop();
	this->print();
	this->pop();
	this->print();
	this->pop();
	this->print();
	this->pop();
	cout << endl;
}

bool Stack::isEmpty()
{
	return this->top == 0; // if the number of items is zero then is empty
}

bool Stack::is_full()
{
	return this->top == SIZE; // if the number of items is equal SIZE then is full
}