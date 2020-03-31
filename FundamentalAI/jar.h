#include <iostream>
#include <chrono>
#include "tree.h"
#include "jar_content.h"

#ifndef JAR_H
#define JAR_H

using namespace std;

class Jar : public Tree<JarContent*> {
private:
	int limitJarA;
	int limitJarB;
	JarContent* goal_;

	bool search_list_explored(JarContent* content); // search in the explored node list
	bool search_list_queue_bfs(JarContent* content); // search in the node list used in the breadth first search
	bool search_list_stack_dfs(JarContent* content); // search in the node list used in the depth first search
	TreeNode<JarContent*>* get_copy_node(TreeNode<JarContent*>* node); // get copy of node
	void create_children_nodes(TreeNode<JarContent*>* node); // create new nodes based in his parent
	void create_child_node(TreeNode<JarContent*>* node, JarContent* nodeValue); // create new node
	bool compare_goal(JarContent* first, JarContent* second);

	bool compare(JarContent* first, JarContent* second) override; // compare two contents
	int manhattan_distance(JarContent* test, JarContent* goal) override;
	int utility_function(JarContent* state) override;

public:
	Jar(JarContent* goal, int limitJarA, int limitJarB);
	~Jar();

	TreeNode<JarContent*>* search_bfs(JarContent* test) override;
	TreeNode<JarContent*>* search_dfs(JarContent* test) override;

	void print_content(JarContent* content) override;
	void test() override;
};

#endif
