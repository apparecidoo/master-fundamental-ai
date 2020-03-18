#include <iostream>
#include "linked_list.h"

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

using namespace std;

template <class T>
class DynamicStack : public LinkedList<T> {
public:
	DynamicStack();
	~DynamicStack();

	void push(T value); // insert a value in the stack
	T pop(); // remove the last value in the stack
	void test() override;
	void print() override;
};

template <class T>
DynamicStack<T>::DynamicStack()
{
}

template <class T>
DynamicStack<T>::~DynamicStack()
{
}

template <class T>
void DynamicStack<T>::push(T value)
{
	this->add_first(value);
}

template <class T>
T DynamicStack<T>::pop()
{
	T value = this->remove_first();

	return value;
}

template <class T>
void DynamicStack<T>::test() {
	
}

template <class T>
void DynamicStack<T>::print()
{

}


#endif
