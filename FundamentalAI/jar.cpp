#include "pch.h"
#include "jar.h"

Jar::Jar(JarNode* goal, int limitJarA, int limitJarB) : Tree<JarNode*>()
{
	this->goal_ = goal;
	this->limitJarA = limitJarA;
	this->limitJarB = limitJarB;
}

Jar::~Jar()
{
	this->Tree<JarNode*>::~Tree();
}

TreeNode<JarNode*>* Jar::search_bfs(JarNode* test)
{
	this->root = new TreeNode<JarNode*>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->queue_bfs_list->enqueue(this->root); // start my queue

	while (!this->queue_bfs_list->is_empty())
	{
		TreeNode<JarNode*>* node = this->queue_bfs_list->dequeue();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare_goal(node->content, this->goal_)) // compare the current node with the goal
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<JarNode*>*>* child = node->children_nodes->get_root();

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

TreeNode<JarNode*>* Jar::search_dfs(JarNode* test)
{
	this->root = new TreeNode<JarNode*>(test, NULL, this->manhattan_distance(test, goal_), 0, this->new_id());
	this->explored_list->clear();
	this->stack_dfs_list->push(this->root);

	while (!this->stack_dfs_list->is_empty())
	{
		TreeNode<JarNode*>* node = this->stack_dfs_list->pop();
		node->explored = true;
		this->explored_list->enqueue(node->content);

		if (this->compare_goal(node->content, this->goal_)) // compare the current node with the goal
			return node;

		this->create_children_nodes(node); // create the new neighbors

		// get the neighbors to be explored
		if (node->has_children()) {
			SimpleNode<TreeNode<JarNode*>*>* child = node->children_nodes->get_root();

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

void Jar::print_content(JarNode* content)
{
	cout << "JarA: " << content->jarA << endl;
	cout << "JarB: " << content->jarB << endl;
	cout << "Operation: " << content->operation << endl;
}

void Jar::test()
{
	std::chrono::time_point<chrono::steady_clock> tStart = std::chrono::high_resolution_clock::now();

	JarNode* jar_test = new JarNode(0, 0, "start");

	JarNode* jar_goal = new JarNode(-1, 2, "goal");
	this->goal_ = jar_goal;

	cout << "Jar Test" << endl;
	this->print_content(jar_test);
	cout << "Jar Goal" << endl;
	this->print_content(jar_goal);

	tStart = std::chrono::high_resolution_clock::now();
	TreeNode<JarNode*>* node;
	node = NULL;
	node = this->search_dfs(jar_test);
	cout << ">>>>>>>>>> DFS RESULT <<<<<<<<< Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tStart).count() << " microseconds" << endl;
	this->print_node(node);
	this->back_tracking(node);

	tStart = std::chrono::high_resolution_clock::now();
	node = NULL;
	node = this->search_bfs(jar_test);
	cout << ">>>>>>>>>> BFS RESULT <<<<<<<<< Time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - tStart).count() << " microseconds" << endl;
	this->print_node(node);
	this->back_tracking(node);
}

bool Jar::search_list_explored(JarNode* content)
{
	SimpleNode<JarNode*>* node = this->explored_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare(node->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

bool Jar::search_list_queue_bfs(JarNode* content)
{
	SimpleNode<TreeNode<JarNode*>*>* node = this->queue_bfs_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

bool Jar::search_list_stack_dfs(JarNode* content)
{
	SimpleNode<TreeNode<JarNode*>*>* node = this->stack_dfs_list->get_root();

	// going to the end
	while (node != NULL)
	{
		if (this->compare(node->content->content, content))
			return true;

		node = node->next_node;
	}

	return false;
}

bool Jar::compare(JarNode* first, JarNode* second)
{
	return first->jarA == second->jarA && first->jarB == second->jarB;
}

bool Jar::compare_goal(JarNode * first, JarNode * second)
{
	return first->jarB == second->jarB;
}

int Jar::manhattan_distance(JarNode * test, JarNode * goal)
{
	return 0;
}

TreeNode<JarNode*>* Jar::get_copy_node(TreeNode<JarNode*>* node)
{
	JarNode* copy = new JarNode(node->content->jarA, node->content->jarB);

	return new TreeNode<JarNode*>(copy, node, 0);
}

void Jar::create_children_nodes(TreeNode<JarNode*>* node)
{
	TreeNode<JarNode*>* move;

	if (node->content->jarA < this->limitJarA) {  // Encher a jarra A
		create_child_node(node, new JarNode(this->limitJarA, node->content->jarB, "Encher a jarra A"));
	}

	if (node->content->jarB < this->limitJarB) { // Encher a jarra B
		create_child_node(node, new JarNode(node->content->jarB, this->limitJarB, "Encher a jarra B"));
	}

	if (node->content->jarA > 0) { // Esvaziar a jarra A
		create_child_node(node, new JarNode(0, node->content->jarB, "Esvaziar a jarra A"));
	}

	if (node->content->jarB > 0) { // Esvaziar a jarra B
		create_child_node(node, new JarNode(node->content->jarA, 0, "Esvaziar a jarra B"));
	}
	
	if (node->content->jarB < this->limitJarB && node->content->jarA > 0) { // Transferir de A para B
		int transf = this->limitJarB - node->content->jarB;
		create_child_node(node, new JarNode(node->content->jarA - transf, node->content->jarB + transf, "Transferir de A para B"));
	}

	if (node->content->jarA < this->limitJarA && node->content->jarB > 0) { // Transferir de B para A
		int transf = this->limitJarA - node->content->jarA;
		create_child_node(node, new JarNode(node->content->jarA + transf, node->content->jarB - transf, "Transferir de B para A"));
	}

	/*cout << "================================ \n";
	print_node_children(node);*/
}

void Jar::create_child_node(TreeNode<JarNode*>* node, JarNode* nodeValue)
{
	TreeNode<JarNode*>* move = this->get_copy_node(node);
	move->content = nodeValue;
	this->set_child_properties(move, this->goal_);
	node->children_nodes->enqueue(move);
}