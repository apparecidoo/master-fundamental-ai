#include <iostream>
#include "simple_node.h"
#include "custom_exception.h"

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

using namespace std;

template <class T>
class LinkedList {
public:
	LinkedList();
	~LinkedList();

	void add_first(T value); // insert a value in the beginning of list
	void add_last(T value); // insert a value in the end of list
	T remove_first(); // remove the last value in the beginning of list
	T remove_last(); // remove the last value in the end of list
	T remove(T value); // remove the last value in the end of list
	int get_number_nodes(); // return the number of nodes in the list
	void remove_number_nodes();
	virtual SimpleNode<T>* get_root(); // get root node
	virtual void reset();
	bool is_empty(); // check if the stack is empty
	bool is_full(); // check if the stack is full
	SimpleNode<T>* search(T content); // search if exists
	void clear(); // remove all nodes from list
	void clearWithoutDelete(); // remove all nodes from list

	virtual bool compare(T first, T second); // compare contents
	virtual void print(); // print all values from list
	virtual void test(); // method to test

protected:
	int number_nodes; // number of nodes in the list
	SimpleNode<T>* root; // first position of queue to be retired

	void deleteNode(SimpleNode<T>* node); // delete the node deallocating memory
	SimpleNode<T>* createNode(T value); // create the node allocating memory
};


template <class T>
LinkedList<T>::LinkedList()
{
	root = NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
	this->clear();
}

template <class T>
void LinkedList<T>::add_first(T value)
{
	try
	{
		if (is_full())
			throw CustomException("**The list is full.");

		if (is_empty()) {
			root = createNode(value); // if is the list is empty, add as root
		}
		else {
			SimpleNode<T>* node = root;

			root = createNode(value); // set the new root
			root->next_node = node; // set next_node from the new root with the old root, so "new_root_node->next_node = old_root"
		}

		this->number_nodes++;
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}
}

template <class T>
void LinkedList<T>::add_last(T value)
{
	try
	{
		if (this->is_empty()) {
			this->root = createNode(value); // if is the list is empty, add as root
		}
		else {
			if (is_full())
				throw CustomException("**The list is full.");

			SimpleNode<T>* node = this->root;

			// going to the end
			while (node->next_node != NULL)
			{
				node = node->next_node;
			}

			node->next_node = this->createNode(value); // allocate memory
		}

		this->number_nodes++;
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}
}

template <class T>
T LinkedList<T>::remove_first()
{
	T value = NULL; // return NULL if something is wrong

	try
	{
		if (is_empty())
			throw CustomException("**The list is empty.");

		SimpleNode<T>* node = this->root;
		this->root = node->next_node; // get the next node and set as root
		value = node->content; // get the value to be returned
		this->deleteNode(node); // deallocate the memory
		this->number_nodes--;
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return value;
}

template <class T>
T LinkedList<T>::remove_last()
{
	T value = NULL; // return NULL if something is wrong

	try
	{
		if (is_empty())
			throw CustomException("**The list is empty.");

		SimpleNode<T>* node = this->root;
		SimpleNode<T>* previous_node = NULL;

		while (node->next_node != NULL)
		{
			previous_node = node; // if was the root, then we need to maintain NULL on previous_node
			node = node->next_node; // got to next node
		}

		if (previous_node != NULL)
			previous_node->next_node = NULL; // remove the link with the next node
		else
			this->root = NULL; // if was the root, remove root_node setting NULL

		value = node->content; // get the value to be returned

		this->deleteNode(node); // deallocate the memory
		this->number_nodes--;
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return value;
}

template<class T>
T LinkedList<T>::remove(T value)
{
	// get next node to be explored
	SimpleNode<T>* node = this->root;
	SimpleNode<T>* aux_node = NULL;
	SimpleNode<T>* previous_node = NULL;

	// finding node
	while (node != NULL)
	{
		if (this->compare(node->content, value)) {
			break;
		}

		previous_node = node;
		node = node->next_node;
	}

	// deleting node
	aux_node = node;
	if (previous_node == NULL) { // root node
		this->root = node->next_node;
	}
	else {
		if (node->next_node == NULL)
			previous_node->next_node = NULL;
		else
			previous_node->next_node = node->next_node;
	}

	delete node;

	return aux_node->content;
}

template <class T>
void LinkedList<T>::print()
{
}

template <class T>
int LinkedList<T>::get_number_nodes()
{
	return this->number_nodes;
}

template<class T>
void LinkedList<T>::remove_number_nodes()
{
	this->number_nodes--;
}

template <class T>
SimpleNode<T>* LinkedList<T>::get_root()
{
	return root;
}

template<class T>
void LinkedList<T>::reset()
{
	this->number_nodes = 0;
	this->root = NULL;
}

template<class T>
SimpleNode<T>* LinkedList<T>::search(T content)
{
	SimpleNode<T>* node = root;

	// going to the end
	while (node != NULL)
	{
		if (compare(node->content, content))
			return node;

		node = node->next_node;
	}

	return NULL;
}

template<class T>
bool LinkedList<T>::compare(T first, T second)
{
	return first == second;
}

template<class T>
void LinkedList<T>::clear()
{
	// cleaning the list
	while (!is_empty())
	{
		remove_first();
	}
}

template<class T>
void LinkedList<T>::clearWithoutDelete()
{
	this->number_nodes = 0;
	this->root = NULL;
}

template <class T>
void LinkedList<T>::test()
{

}

template <class T>
bool LinkedList<T>::is_empty()
{
	return root == NULL; // if the root is null then the list is empty
}

template <class T>
bool LinkedList<T>::is_full()
{
	try
	{
		SimpleNode<T>* node = createNode(0); // allocate memory

		if (node == NULL) {
			cout << "***Error: Cannot allocate memory, Node is null." << endl;
			return true;
		}

		this->deleteNode(node);

		return false;
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
		return true;
	}
	catch (const std::exception& ex)
	{
		cout << "***Error: " << ex.what() << endl;
		return true;
	}
}

template <class T>
void LinkedList<T>::deleteNode(SimpleNode<T> * node)
{
	try
	{
		if (node == NULL)
			throw CustomException("**Error: The node cannot be null on delete.");

		delete node; // deallocate memory
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

}

template <class T>
SimpleNode<T> * LinkedList<T>::createNode(T value)
{
	SimpleNode<T>* node = NULL;

	try
	{
		node = new SimpleNode<T>(value); // allocate memory

		if (node == NULL)
			throw CustomException("**Error: The node cannot be allocated.");
	}
	catch (CustomException& ex)
	{
		ex.showMessage();
	}

	return node;
}


#endif
