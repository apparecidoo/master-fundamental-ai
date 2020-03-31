#include <iostream>
#include <chrono>
#include "tree.h"

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

	bool compare(int** first, int** second) override;
	int manhattan_distance(int** test, int** goal) override;
	int utility_function(int** state) override;
public:
	TicTacToe(int playersNumber = 1);
	~TicTacToe();

	void start();
	void print_board();
	void print_content(int** content) override;
};

#endif
