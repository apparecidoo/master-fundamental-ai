#include <iostream>
#include <chrono>
#include "tree.h"
#include "puzzle_type.h"

#ifndef PUZZLE_H
#define PUZZLE_H

using namespace std;

template <class T>
class Puzzle : public Tree<T> {
private:
	int size_puzzle;
	T goal_;

	bool search_list_explored(T content); // search in the explored node list
	bool search_list_queue_bfs(T content); // search in the node list used in the breadth first search
	bool search_list_stack_dfs(T content); // search in the node list used in the depth first search
	bool search_list_a_star(T content); // search in the node list used in the A* search
	TreeNode<T>* move_zero_up(TreeNode<T>* node); // move zerto to up
	TreeNode<T>* move_zero_down(TreeNode<T>* node); // move zerto to down
	TreeNode<T>* move_zero_right(TreeNode<T>* node); // move zerto to right
	TreeNode<T>* move_zero_left(TreeNode<T>* node); // move zerto to left
	TreeNode<T>* get_copy_node(TreeNode<T>* node); // get copy of node
	void create_children_nodes(TreeNode<T>* node); // create new nodes based in his parent

	int get_inversions_count(T content);
	bool is_solvable(T puzzle);
	bool compare(T first, T second) override; // compare two contents
	int manhattan_distance(T test, T goal) override;
	TreeNode<T>* a_star_get_next_node_to_explore() override;

public:
	Puzzle(T goal, int size_puzzle);
	Puzzle(T goal, PuzzleType puzzle_type);
	~Puzzle();

	TreeNode<T>* search_bfs(T test) override;
	TreeNode<T>* search_dfs(T test) override;
	TreeNode<T>* search_a_star(T test) override;
	TreeNode<T>* search_hill_climbing(T test) override;

	void print_content(T content) override;
	void print_node(TreeNode<T>* node) override;
	void print_node_children(TreeNode<T>* node) override;
	void print_children(TreeNode<T>* node) override;
	void test() override;
};

template <class T>
Puzzle<T>::Puzzle(T goal, int size_puzzle) : Tree<T>()
{
	this->goal_ = goal;
	this->size_puzzle = size_puzzle;
}

template<class T>
Puzzle<T>::Puzzle(T goal, PuzzleType puzzle_type)
{
	switch (puzzle_type)
	{
	case Puzzle8:
		this->size_puzzle = 3;
		break;
	case Puzzle15:
		this->size_puzzle = 4;
		break;
	case Puzzle24:
		this->size_puzzle = 5;
		break;
	case Puzzle35:
		this->size_puzzle = 6;
		break;
	case Puzzle48:
		this->size_puzzle = 7;
		break;
	default:
		break;
	}

	this->goal_ = goal;
}

template <class T>
Puzzle<T>::~Puzzle()
{
	this->Tree<T>::~Tree();
}

template <class T>
TreeNode<T>* Puzzle<T>::search_bfs(T test)
{
	if (!this->is_solvable(test))
		throw CustomException("This puzzle is not solvable");

	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->queue_bfs_list->enqueue(this->root); // start my queue

	while (!this->queue_bfs_list->is_empty())
	{
		TreeNode<T>* node = this->queue_bfs_list->dequeue();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare(node->content, this->goal_)) // compare the current node with the goal
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (!this->search_list_explored(child->content->content) && !this->search_list_queue_bfs(child->content->content)) // cannot contains in the explored list and list to be explored
				{
					this->queue_bfs_list->enqueue(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template <class T>
TreeNode<T>* Puzzle<T>::search_dfs(T test)
{
	if (!this->is_solvable(test))
		throw CustomException("This puzzle is not solvable");

	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->stack_dfs_list->push(this->root);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<T>* node = this->stack_dfs_list->pop();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare(node->content, this->goal_)) // compare the current node with the goal
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (!this->search_list_explored(child->content->content) && !this->search_list_stack_dfs(child->content->content)) // cannot contains in the explored list and list to be explored
				{
					this->stack_dfs_list->push(child->content);
				}

				child = child->next_node;
			}
		}
	}

	return NULL;
}

template<class T>
TreeNode<T>* Puzzle<T>::search_a_star(T test)
{
	if (!this->is_solvable(test))
		throw CustomException("This puzzle is not solvable");

	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->a_star_list->add_last(this->root);

	while (!this->a_star_list->is_empty())
	{
		TreeNode<T>* node = this->a_star_get_next_node_to_explore();
		node->explored = true;
		this->explored_list->add_last(node->content);

		if (this->compare(node->content, this->goal_)) // compare the current node with the goal
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (!this->search_list_explored(child->content->content) && !this->search_list_a_star(child->content->content))
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
TreeNode<T>* Puzzle<T>::search_hill_climbing(T test)
{
	this->root = new TreeNode<T>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	TreeNode<T>* node = this->root;
	TreeNode<T>* node_to_validate = node;

	while (node != NULL)
	{
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare(node->content, this->goal_)) // compare the current node with the goal
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();
			node_to_validate = node;
			node = NULL;

			while (child != NULL)
			{
				// check if was not explored and is not in the stack to be explored
				if (!this->search_list_explored(child->content->content) && child->content->f_score <= node_to_validate->f_score)
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
void Puzzle<T>::print_content(T content)
{
	for (int i = 0; i < this->size_puzzle; i++)
	{
		for (int j = 0; j < this->size_puzzle; j++)
		{
			cout << content[i][j] << "   ";
		}

		cout << endl;
	}
}

template<class T>
void Puzzle<T>::print_node(TreeNode<T>* node)
{
	if (node == NULL) {
		cout << "Node is null or empty" << endl;
		return;
	}

	cout << "Id: " << node->id << " | g_score: " << node->g_score << " | h_score: " << node->h_score << " | f_score " << node->f_score << endl;
	this->print_content(node->content);
}

template<class T>
void Puzzle<T>::print_node_children(TreeNode<T>* node)
{
	cout << "Id: " << node->id << " | g_score: " << node->g_score << " | h_score: " << node->h_score << " | f_score " << node->f_score << endl;
	this->print_children(node);
}

template<class T>
void Puzzle<T>::print_children(TreeNode<T>* node)
{
	if (node != NULL) {
		if (node->has_children()) {
			SimpleNode<TreeNode<T>*>* child = node->children_nodes->get_root();

			while (child != NULL)
			{
				this->print_node(child->content);
				child = child->next_node;
			}
		}
	}
}

template<class T>
void Puzzle<T>::test()
{
	std::chrono::time_point<chrono::steady_clock> tStart = std::chrono::high_resolution_clock::now();

	int** puzzle_test = new int*[3];
	puzzle_test[0] = new int[3]{ 4, 1, 6 };
	puzzle_test[1] = new int[3]{ 3, 2, 8 };
	puzzle_test[2] = new int[3]{ 7, 0, 5 };

	int** goal_test = new int*[3];
	goal_test[0] = new int[3]{ 1, 2, 3 };
	goal_test[1] = new int[3]{ 4, 5, 6 };
	goal_test[2] = new int[3]{ 7, 8, 0 };
	this->goal_ = goal_test;
	this->size_puzzle = 3;
	
	cout << "Puzzle Test" << endl;
	this->print_content(puzzle_test);
	cout << "Puzzle Goal" << endl;
	this->print_content(goal_test);

	tStart = std::chrono::high_resolution_clock::now();
	TreeNode<int**>* node;
	node = NULL;
	node = this->search_dfs(puzzle_test);
	cout << ">>>>>>>>>> DFS RESULT <<<<<<<<< Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tStart).count() << " microseconds" << endl;
	this->print_node(node);
	//this->back_tracking(node);

	tStart = std::chrono::high_resolution_clock::now();
	node = NULL;
	node = this->search_bfs(puzzle_test);
	cout << ">>>>>>>>>> BFS RESULT <<<<<<<<< Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tStart).count() << " microseconds" << endl;
	this->print_node(node);
	//this->back_tracking(node);

	tStart = std::chrono::high_resolution_clock::now();
	node = NULL;
	node = this->search_a_star(puzzle_test);
	cout << ">>>>>>>>>> A* RESULT <<<<<<<<< Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tStart).count() << " microseconds" << endl;
	this->print_node(node);
	/*this->back_tracking(node);*/

	tStart = std::chrono::high_resolution_clock::now();
	node = NULL;
	node = this->search_hill_climbing(puzzle_test);
	cout << ">>>>>>>>>> HILL CLIMBING RESULT <<<<<<<<< Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tStart).count() << " microseconds" << endl;
	this->print_node(node);
	/*this->back_tracking(node);*/
}

template<class T>
bool Puzzle<T>::search_list_explored(T content)
{
	SimpleNode<T>* node = this->explored_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare(node->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
bool Puzzle<T>::search_list_queue_bfs(T content)
{
	SimpleNode<TreeNode<T>*>* node = this->queue_bfs_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
bool Puzzle<T>::search_list_stack_dfs(T content)
{
	SimpleNode<TreeNode<T>*>* node = this->stack_dfs_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
bool Puzzle<T>::search_list_a_star(T content)
{
	if (!this->a_star_list->is_empty())
		return false;

	SimpleNode<TreeNode<T>*>* node = this->a_star_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

template<class T>
int Puzzle<T>::get_inversions_count(T content)
{
	int inv_count = 0, count = 0;
	int parts_num = this->size_puzzle * this->size_puzzle; // 9 for puzzle 8
	int* arr = new int[parts_num];

	for (int i = 0; i < this->size_puzzle; i++) {
		for (int j = 0; j < this->size_puzzle; j++) {
			arr[count] = content[i][j];
				count++;
		}
	}

	for (int i = 0; i < parts_num - 1; i++) {
		for (int j = i + 1; j < parts_num; j++) {
			if (arr[j] && arr[i] && arr[i] > arr[j]) {
				inv_count++;
			}
		}
	}

	return inv_count;
}

template<class T>
bool Puzzle<T>::is_solvable(T puzzle)
{
	return (this->get_inversions_count(puzzle) % 2 == 0); // return true if inversion count is even.
}

template<class T>
bool Puzzle<T>::compare(T first, T second)
{
	for (int i = 0; i < this->size_puzzle; i++)
	{
		for (int j = 0; j < this->size_puzzle; j++)
		{
			if (first[i][j] != second[i][j]) {
				return false;
			}
		}
	}

	return true;
}

template<class T>
int Puzzle<T>::manhattan_distance(T test, T goal)
{
	int sum = 0;
	int i_test = 0;
	int j_test = 0;
	int i_goal = 0;
	int j_goal = 0;

	// get the value to test
	for (i_test = 0; i_test < this->size_puzzle; i_test++)
	{
		for (j_test = 0; j_test < this->size_puzzle; j_test++)
		{
			bool found = false;

			// search in the goal
			for (i_goal = 0; i_goal < this->size_puzzle; i_goal++)
			{
				for (j_goal = 0; j_goal < this->size_puzzle; j_goal++)
				{
					if (test[i_test][j_test] == goal[i_goal][j_goal]) {
						found = true;
						break;
					}
				}

				if (found)
					break;

				j_goal = 0;
			}

			if (found) {
				sum += abs((i_test - i_goal) + (j_test - j_goal));
				i_goal = 0;
				j_goal = 0;
			}
			else {
				throw CustomException("Error to find the manhattan distance");
			}
		}
	}

	return sum;
}

template<class T>
TreeNode<T>* Puzzle<T>::a_star_get_next_node_to_explore()
{
	TreeNode<T>* value = NULL;

	// get next node to be explored
	SimpleNode<TreeNode<T>*>* root = this->a_star_list->get_root();
	SimpleNode<TreeNode<T>*>* node = root;
	SimpleNode<TreeNode<T>*>* best_node = node;
	SimpleNode<TreeNode<T>*>* previous_best_node = NULL;
	SimpleNode<TreeNode<T>*>* previous_node = NULL;

	// finding node
	while (node != NULL)
	{
		if (best_node->content->f_score >= node->content->f_score) {
			previous_best_node = previous_node;
			best_node = node;
		}

		if (node->next_node != NULL)
			previous_node = node;

		node = node->next_node;
	}

	// deleting node
	if (previous_best_node == NULL) { // root node
		value = this->a_star_list->remove_first();
	}
	else {
		if (best_node->next_node == NULL) {
			value = this->a_star_list->remove_last();
		}
		else {
			previous_best_node->next_node = best_node->next_node;
			value = best_node->content;
			delete best_node;
			this->a_star_list->remove_number_nodes();
		}
	}

	return value;
}

template<class T>
TreeNode<T>* Puzzle<T>::move_zero_up(TreeNode<T>* node)
{
	TreeNode<int**>* move = NULL;
	bool search_zero = false;
	int i = 0;
	int j = 0;

	if (node == NULL)
		throw CustomException("move_zero_up - node is null or empty");

	// find zero position
	for (i = 0; i < this->size_puzzle; i++)
	{
		for (j = 0; j < this->size_puzzle; j++)
		{
			if (node->content[i][j] == 0) {
				search_zero = true;
				break;
			}
		}

		if (search_zero)
			break;
	}

	if (i - 1 < 0) {
		//throw CustomException("Cannot move left");
		return NULL;
	}

	move = this->get_copy_node(node);
	move->content[i][j] = move->content[i - 1][j];
	move->content[i - 1][j] = 0;

	// check if the node is solvable
	if (!this->is_solvable(move->content))
		return NULL;

	this->set_child_properties(move, this->goal_);
	node->children_nodes->enqueue(move);

	return move;
}

template<class T>
TreeNode<T>* Puzzle<T>::move_zero_down(TreeNode<T>* node)
{
	TreeNode<int**>* move = NULL;
	bool search_zero = false;
	int i = 0;
	int j = 0;

	if (node == NULL)
		throw CustomException("move_zero_down - node is null or empty");

	// find zero position
	for (i = 0; i < this->size_puzzle; i++)
	{
		for (j = 0; j < this->size_puzzle; j++)
		{
			if (node->content[i][j] == 0) {
				search_zero = true;
				break;
			}
		}

		if (search_zero)
			break;
	}

	if (i + 1 > this->size_puzzle - 1) {
		//throw CustomException("Cannot move right");
		return NULL;
	}

	move = this->get_copy_node(node);
	move->content[i][j] = move->content[i + 1][j];
	move->content[i + 1][j] = 0;

	// check if the node is solvable
	if (!this->is_solvable(move->content))
		return NULL;

	this->set_child_properties(move, this->goal_);
	node->children_nodes->enqueue(move);

	return move;
}

template<class T>
TreeNode<T>* Puzzle<T>::move_zero_right(TreeNode<T>* node)
{
	TreeNode<int**>* move = NULL;
	bool search_zero = false;
	int i = 0;
	int j = 0;

	if (node == NULL)
		throw CustomException("move_zero_right - node is null or empty");

	// find zero position
	for (i = 0; i < this->size_puzzle; i++)
	{
		for (j = 0; j < this->size_puzzle; j++)
		{
			if (node->content[i][j] == 0) {
				search_zero = true;
				break;
			}
		}

		if (search_zero)
			break;
	}

	if (j + 1 > this->size_puzzle - 1) {
		//throw CustomException("Cannot move down");
		return NULL;
	}

	move = this->get_copy_node(node);
	move->content[i][j] = move->content[i][j + 1];
	move->content[i][j + 1] = 0;
	
	// check if the node is solvable
	if (!this->is_solvable(move->content))
		return NULL;

	this->set_child_properties(move, this->goal_);
	node->children_nodes->enqueue(move);

	return move;
}

template<class T>
TreeNode<T>* Puzzle<T>::move_zero_left(TreeNode<T>* node)
{
	TreeNode<int**>* move = NULL;
	bool search_zero = false;
	int i = 0;
	int j = 0;

	if (node == NULL)
		throw CustomException("move_zero_left - node is null or empty");

	// find zero position
	for (i = 0; i < this->size_puzzle; i++)
	{
		for (j = 0; j < this->size_puzzle; j++)
		{
			if (node->content[i][j] == 0) {
				search_zero = true;
				break;
			}
		}

		if (search_zero)
			break;
	}

	if (j - 1 < 0) {
		//throw CustomException("Cannot move up");
		return NULL;
	}

	move = this->get_copy_node(node);
	move->content[i][j] = move->content[i][j - 1];
	move->content[i][j - 1] = 0;
	
	// check if the node is solvable
	if (!this->is_solvable(move->content))
		return NULL;

	this->set_child_properties(move, this->goal_);
	node->children_nodes->enqueue(move);

	return move;
}

template<class T>
TreeNode<T>* Puzzle<T>::get_copy_node(TreeNode<T>* node)
{
	int** copy = new int*[this->size_puzzle];

	for (int i = 0; i < this->size_puzzle; i++)
	{
		copy[i] = new int[this->size_puzzle];

		for (int j = 0; j < this->size_puzzle; j++)
		{
			copy[i][j] = node->content[i][j];
		}
	}

	return new TreeNode<int**>(copy, node, 0);
}

template<class T>
void Puzzle<T>::create_children_nodes(TreeNode<T>* node)
{
	TreeNode<T>* left_move = this->move_zero_left(node);
	TreeNode<T>* down_move = this->move_zero_down(node);
	TreeNode<T>* right_move = this->move_zero_right(node);
	TreeNode<T>* up_move = this->move_zero_up(node);
	
	//if (left_move != NULL) // up
	//	this->print_node(left_move);
	//if (down_move != NULL) // right
	//	this->print_node(down_move);
	//if (right_move != NULL) // down
	//	this->print_node(right_move);
	//if (up_move != NULL) // left
	//	this->print_node(up_move);
}

#endif
