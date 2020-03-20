#include <iostream>
#include "tree_node.h"
#include "custom_exception.h"
#include "linked_list.h"
#include "stack_dynamic.h"
#include "queue_dynamic.h"

#ifndef TREE_H
#define TREE_H

using namespace std;

template <class T>
class Tree
{

protected:
	TreeNode<T>* root;
	int id;
	int g_score;
	DynamicQueue<TreeNode<T>*>* queue_bfs_list; // queue list used for breadth first search
	DynamicStack<TreeNode<T>*>* stack_dfs_list; // stack list used for depth first search
	LinkedList<TreeNode<T>*>* a_star_list; // queue list used for A*
	DynamicQueue<T>* explored_list; // list of explored nodes

	int new_id(); // get a new id	
	virtual void set_child_properties(TreeNode<T>* node, T goal); // set properties for child of node
	virtual bool compare(T first, T second); // comparing two contents
	virtual int manhattan_distance(T test, T goal) = 0; // calculate manhattan distance
	virtual TreeNode<T>* a_star_get_next_node_to_explore(); // method to get the next node to be explore in the search A*

public:
	Tree();
	~Tree();
	void remove_cascate(T content); // remove the node and his children
	virtual TreeNode<T>* search_bfs(T content); // search using breadth first search
	virtual TreeNode<T>* search_dfs(T content); // search using depth first search
	virtual TreeNode<T>* search_a_star(T content); // search using A*
	virtual TreeNode<T>* search_hill_climbing(T content); // search using hill climbing
	void back_tracking(TreeNode<T>* node);
	virtual void print_content(T content); // print the node content
	virtual void print_node(TreeNode<T>* node); // print the node properties and content
	virtual void print_node_children(TreeNode<T>* node); // print the node and his children
	virtual void print_children(TreeNode<T>* node); // print the node children
	virtual void print_tree(); // print the tree
	virtual void test();
};

template <class T>
Tree<T>::Tree()
{
	this->g_score = 0;
	this->root = NULL;
	this->id = 1;
	this->queue_bfs_list = new DynamicQueue<TreeNode<T>*>();
	this->stack_dfs_list = new DynamicStack<TreeNode<T>*>();
	this->explored_list = new DynamicQueue<T>();
	this->a_star_list = new LinkedList<TreeNode<T>*>();
}

template<class T>
Tree<T>::~Tree()
{
	if (root != NULL)
		this->remove_cascate(root->content);

	this->explored_list->clear();
	this->stack_dfs_list->clear();
	this->queue_bfs_list->clear();
}

template<class T>
int Tree<T>::new_id()
{
	return this->id++;
}

template<class T>
void Tree<T>::back_tracking(TreeNode<T>* node)
{
	cout << endl << ">> Backtracking: " << endl;
	DynamicStack<TreeNode<T>*>* list = new DynamicStack<TreeNode<T>*>();
	TreeNode<T>* aux_node = node;

	while (aux_node != NULL)
	{
		list->push(aux_node);
		aux_node = aux_node->parent;
	}

	while (!list->is_empty())
	{
		aux_node = list->pop();
		cout << "" << endl;
		this->print_node(aux_node);
	}
}

template<class T>
void Tree<T>::set_child_properties(TreeNode<T>* node, T goal)
{
	node->h_score = this->manhattan_distance(node->content, goal);
	node->g_score = node->parent->g_score + 1;
	node->f_score = node->h_score + node->g_score;
	node->id = this->new_id();
}

template<class T>
void Tree<T>::remove_cascate(T content)
{
	this->explored_list->clear();
	TreeNode<T>* nodeRoot = this->search_dfs(content);
	this->stack_dfs_list->push(nodeRoot);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (!child->content->explored && this->stack_dfs_list->search(child->content) == NULL)
				{
					stack_dfs_list->push(child->content);
				}

				child = child->next_node;
			}
		}
	}
}

template<class T>
TreeNode<T>* Tree<T>::search_bfs(T content)
{
	this->explored_list->clear();
	this->queue_bfs_list->enqueue(root); // start my queue

	while (!this->queue_bfs_list->is_empty())
	{
		TreeNode<T>* node = this->queue_bfs_list->dequeue();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content)) // check if is the response
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (this->explored_list->search(child->content->content) == NULL && this->queue_bfs_list->search(child->content) == NULL)
				{
					this->queue_bfs_list->enqueue(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Tree<T>::search_dfs(T content)
{
	this->explored_list->clear();
	this->stack_dfs_list->push(root);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content)) // check if is the response
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (this->explored_list->search(child->content->content) == NULL && this->stack_dfs_list->search(child->content) == NULL)
				{
					stack_dfs_list->push(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Tree<T>::search_a_star(T content)
{
	this->explored_list->clear();
	this->a_star_list->add_last(this->root);

	while (!this->a_star_list->is_empty())
	{
		TreeNode<T>* node = this->a_star_get_next_node_to_explore();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content)) // check if is the response
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (this->explored_list->search(child->content->content) == NULL && this->a_star_list->search(child->content) == NULL)
				{
					this->a_star_list->add_last(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Tree<T>::search_hill_climbing(T content)
{
	this->explored_list->clear();
	TreeNode<T>* node = root;
	TreeNode<T>* node_to_validate = node;

	while (node != NULL)
	{
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (compare(node->content, content)) // check if is the response
			return node;

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();
			node_to_validate = node;
			node = NULL;

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (this->explored_list->search(child->content->content) == NULL && child->content->f_score <= node_to_validate->f_score)
				{
					node = child->content;
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
void Tree<T>::print_content(T content)
{
	throw CustomException("print_content - Method not implemented");
}

template<class T>
void Tree<T>::print_node(TreeNode<T>* node)
{
	throw CustomException("print_node - Method not implemented");
}

template<class T>
void Tree<T>::print_node_children(TreeNode<T>* node)
{
	throw CustomException("print_node_children - Method not implemented");
}

template<class T>
void Tree<T>::print_children(TreeNode<T>* node)
{
	throw CustomException("print_children - Method not implemented");
}

template<class T>
void Tree<T>::print_tree()
{
	this->print_node_children(this->root);
}

template<class T>
void Tree<T>::test()
{
	throw CustomException("test - Method not implemented");
}

template<class T>
bool Tree<T>::compare(T first, T second)
{
	return first == second;
}

template<class T>
TreeNode<T>* Tree<T>::a_star_get_next_node_to_explore()
{
	TreeNode<T>* value = NULL;

	// get next node to be explored
	SimpleNode<TreeNode<T>*>* node = this->a_star_list->get_root();
	SimpleNode<TreeNode<T>*>* best_node = node;
	SimpleNode<TreeNode<T>*>* previous_node = NULL;

	// finding node
	while (node != NULL)
	{
		if (best_node->content->f_score >= node->content->f_score) {
			best_node = node;
		}

		if (node->next_node != NULL)
			previous_node = node;

		node = node->next_node;
	}

	value = this->a_star_list->remove(node->content);

	return value;
}


#endif
