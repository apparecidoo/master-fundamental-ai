#include "pch.h"
#include "queue.h"

Queue::Queue()
{
	first_position = 0;
	last_position = 0;
	number_values = 0;
}

Queue::~Queue()
{
	first_position = 0;
	last_position = 0;
	number_values = 0;
}

void Queue::enqueue(int value)
{
	if (!is_full()) {
		values[last_position] = value; // set the value in the array
		addQueue(); // calculate the next position to be add

		cout << endl << "Enqueue number: " << value << endl;
	}
	else {
		cout << endl << "**The queue is full." << endl;
	}
}

int Queue::dequeue()
{
	int value = 1; // return -1 if something is wrong

	if (!isEmpty()) {
		value = values[first_position]; // get the value
		subQueue(); // calculate the next position to be retired

		cout << endl << "Dequeue number: " << value << endl;
	}
	else {
		cout << endl << "**The queue is empty." << endl;
	}

	return value;
}

void Queue::print()
{
	cout << endl << "Values from Queue: " << endl;
	cout << "[begin] - ";

	// sweeping the array to print in the screen
	int i = first_position;
	while (i != last_position)
	{
		i = i % SIZE;
		cout << values[i] << " | ";
		i++;
	}

	cout << " - [end]" << endl;
}

void Queue::test()
{
	this->enqueue(10);
	this->print();
	this->enqueue(9);
	this->print();
	this->enqueue(8);
	this->print();
	this->dequeue();
	this->print();
	this->dequeue();
	this->print();
	this->dequeue();
	this->print();
	this->dequeue();
	this->print();

	cout << endl;
}

bool Queue::isEmpty()
{
	return number_values == 0; // if the number of items from queue is zero then is empty
}

bool Queue::is_full()
{
	return number_values == SIZE; // if the number of items from queue is equal SIZE then is full
}

void Queue::addQueue()
{
	last_position = (last_position + 1) % SIZE; // push a value and then add 1 for the next value to be added, because is a circular queue
	number_values++; // add +1 from total number
}

void Queue::subQueue()
{
	first_position = (first_position + 1) % SIZE; // pop a value and then add 1 for the next value to be retired, because is a circular queue
	number_values--; // sub -1 from total number
}
