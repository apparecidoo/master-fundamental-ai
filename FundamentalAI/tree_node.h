#include <iostream>
#include "linked_list.h"
#include "queue_dynamic.h"

#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>
class TreeNode
{

public:
	TreeNode<T>* parent; // pointer node to his parent
	DynamicQueue<TreeNode<T>*>* children_nodes; // list of children

	int id; // identification of node, this is unique
	int h_score; // number of misplaced tiles
	int g_score; // node height from tree
	int f_score; // evaluation function
	int u_score; // utility function
	int level; // tree level
	bool explored; // if the node was explored or not
	T content; // value of the node

	TreeNode(T value, TreeNode<T>* parent, int h_score = 0, int g_score = 0, int id = 0, int u_score = 0);
	bool has_children(); // check if has children
	bool has_child_to_explore(); // check if had any child to be explored
	TreeNode<T>* get_next_to_explore();	 // get the next node that was not explored
};


template <class T>
TreeNode<T>::TreeNode(T value, TreeNode<T>* parent, int h_score, int g_score, int id, int u_score)
{
	this->id = id;
	this->h_score = h_score;
	this->g_score = g_score;
	this->f_score = h_score + g_score;
	this->u_score = u_score;
	this->content = value;
	this->children_nodes = new DynamicQueue<TreeNode<T>*>();
	this->parent = parent;
	this->explored = false;
}

template<class T>
bool TreeNode<T>::has_children()
{
	return !this->children_nodes->is_empty();
}

template<class T>
bool TreeNode<T>::has_child_to_explore()
{
	bool has = false;

	SimpleNode<TreeNode<T>*>* simpleNode = this->children_nodes->get_root();

	while (simpleNode != NULL)
	{
		if (!simpleNode->content->explored) {
			has = true;
			break;
		}

		simpleNode = simpleNode->next_node;
	}

	return has;
}

template<class T>
TreeNode<T>* TreeNode<T>::get_next_to_explore()
{
	SimpleNode<TreeNode<T>*>* simpleNode = this->children_nodes->get_root();

	while (simpleNode != NULL)
	{
		if (!simpleNode->content->explored) {
			return simpleNode->content;
		}
	}

	return NULL;
}

#endif
