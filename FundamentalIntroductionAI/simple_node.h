#include <iostream>

#ifndef SIMPLE_NODE_H
#define SIMPLE_NODE_H

using namespace std;

template <class T>
class SimpleNode
{
public:
	SimpleNode(T value);

	T content; // value of the node
	SimpleNode* next_node; // pointer for the next node
};

template <class T>
SimpleNode<T>::SimpleNode(T value)
{
	this->content = value;
	next_node = NULL;
}

#endif
