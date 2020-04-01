#include <iostream>
#include <chrono>
#include "tree.h"
#include <thread>
#include <chrono>

#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

using namespace std;

class TicTacToe : public Tree<int**> {
private:
	int** _board;
	int _playersNumber;
	int _boardSize = 3;
	void single_player();
	void multiplayer();
	bool stop_game();
	void print_positions();
	bool mark(int position, int player);
	bool has_winner();
	int chances_to_win(int** state, int player);

	bool compare(int** first, int** second) override;
	int manhattan_distance(int** test, int** goal) override;
	int utility_function(int** state) override;
	int** minimax(int** content, int levels) override;

	void create_children_nodes(TreeNode<int**>* node, int player, int maxLevel);
	TreeNode<int**>* get_copy_node(TreeNode<int**>* node); // get copy of node

public:
	TicTacToe(int playersNumber = 1);
	~TicTacToe();

	void start();
	void print_board();
	void print_content(int** content) override;
};

#endif
