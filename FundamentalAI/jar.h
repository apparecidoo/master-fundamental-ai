#include <iostream>
#include <chrono>
#include "tree.h"
#include "jar_node.h"

#ifndef JAR_H
#define JAR_H

using namespace std;

class Jar : public Tree<JarNode*> {
private:
	int limitJarA;
	int limitJarB;
	JarNode* goal_;

	bool search_list_explored(JarNode* content); // search in the explored node list
	bool search_list_queue_bfs(JarNode* content); // search in the node list used in the breadth first search
	bool search_list_stack_dfs(JarNode* content); // search in the node list used in the depth first search
	TreeNode<JarNode*>* get_copy_node(TreeNode<JarNode*>* node); // get copy of node
	void create_children_nodes(TreeNode<JarNode*>* node); // create new nodes based in his parent
	void create_child_node(TreeNode<JarNode*>* node, JarNode* nodeValue); // create new node
	bool compare_goal(JarNode* first, JarNode* second);

	bool compare(JarNode* first, JarNode* second) override; // compare two contents
	int manhattan_distance(JarNode* test, JarNode* goal) override;
public:
	Jar(JarNode* goal, int limitJarA, int limitJarB);
	~Jar();

	TreeNode<JarNode*>* search_bfs(JarNode* test) override;
	TreeNode<JarNode*>* search_dfs(JarNode* test) override;

	void print_content(JarNode* content) override;
	void print_node(TreeNode<JarNode*>* node) override;
	void print_node_children(TreeNode<JarNode*>* node) override;
	void print_children(TreeNode<JarNode*>* node) override;
	void test() override;
};

#endif
