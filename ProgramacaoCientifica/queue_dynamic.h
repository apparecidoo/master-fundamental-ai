#include <iostream>
#include "linked_list.h"

#ifndef QUEUE_DYNAMIC_H
#define QUEUE_DYNAMIC_H

using namespace std;

template <class T>
class DynamicQueue : public LinkedList<T> {
public:
	DynamicQueue();
	~DynamicQueue();

	void enqueue(T value); // insert a value in the queue
	T dequeue(); // remove the last value in the queue
	void test() override;
	void print() override;
	SimpleNode<T>* get_root() override; // get root node
};

template <class T>
DynamicQueue<T>::DynamicQueue()
{
}

template <class T>
DynamicQueue<T>::~DynamicQueue()
{
}

template <class T>
void DynamicQueue<T>::enqueue(T value)
{
	this->add_last(value);
}

template <class T>
T DynamicQueue<T>::dequeue()
{
	T value = this->remove_first();

	return value;
}

template <class T>
void DynamicQueue<T>::test()
{
	
}

template <class T>
void DynamicQueue<T>::print()
{

}

template<class T>
SimpleNode<T>* DynamicQueue<T>::get_root()
{
	return this->root;
}


#endif