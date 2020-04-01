#include "pch.h"
#include "tic_tac_toe.h"

TicTacToe::TicTacToe(int playersNumber)
{
	_playersNumber = playersNumber;
	_board = new int*[_boardSize];
	for (int i = 0; i < _boardSize; i++)
	{
		_board[i] = new int[_boardSize];
		for (int j = 0; j < _boardSize; j++)
		{
			_board[i][j] = NULL;
		}
	}
}

TicTacToe::~TicTacToe()
{
}

void TicTacToe::start()
{
	if (_playersNumber == 1) {
		single_player();
	}
	else {
		multiplayer();
	}
}

void TicTacToe::print_board()
{
	cout << "== Board ==" << endl;
	print_content(this->_board);
	cout << "===========" << endl << endl;
}

void TicTacToe::print_content(int** content)
{
	for (int i = 0; i < this->_boardSize; i++)
	{
		for (int j = 0; j < this->_boardSize; j++)
		{
			cout << content[i][j] << "   ";
		}

		cout << endl;
	}
}

void TicTacToe::single_player()
{
	int currentPlayer = 1;
	int position = -1;
	bool tryAgain = true;
	while (!stop_game())
	{
		system("cls");
		print_board();
		if (currentPlayer == 1) {
			while (tryAgain)
			{
				cout << "Player " << currentPlayer << ":" << endl;
				print_positions();
				cin >> position;
				tryAgain = !mark(position, currentPlayer);
			}
		}
		else {
			this_thread::sleep_for(std::chrono::milliseconds(2000));
			this->_board = minimax(this->_board, 4);
		}
		cout << endl;
		tryAgain = true;
		currentPlayer = currentPlayer == 1 ? 2 : 1;
	}
}

void TicTacToe::multiplayer()
{
	int currentPlayer = 1;
	int position = -1;
	bool tryAgain = true;
	while (!stop_game())
	{
		system("cls");
		print_board();
		while (tryAgain)
		{
			cout << "Player " << currentPlayer << ":" << endl;
			print_positions();
			cin >> position;
			tryAgain = !mark(position, currentPlayer);
		}
		cout << endl;
		tryAgain = true;
		currentPlayer = currentPlayer == 1 ? 2 : 1;
	}
}

bool TicTacToe::stop_game()
{
	if (has_winner())
		return true;

	for (int i = 0; i < _boardSize; i++)
	{
		for (int j = 0; j < _boardSize; j++)
		{
			if (_board[i][j] == NULL)
				return false;
		}
	}

	return true;
}

void TicTacToe::print_positions()
{
	cout << "Choose one position to mark: " << endl;
	cout << "| 0 1 2 |" << endl;
	cout << "| 3 4 5 |" << endl;
	cout << "| 6 7 8 |" << endl;
}

bool TicTacToe::mark(int position, int player)
{
	int i, j;

	switch (position)
	{
	case 0:
		i = 0;
		j = 0;
		break;
	case 1:
		i = 0;
		j = 1;
		break;
	case 2:
		i = 0;
		j = 2;
		break;
	case 3:
		i = 1;
		j = 0;
		break;
	case 4:
		i = 1;
		j = 1;
		break;
	case 5:
		i = 1;
		j = 2;
		break;
	case 6:
		i = 2;
		j = 0;
		break;
	case 7:
		i = 2;
		j = 1;
		break;
	case 8:
		i = 2;
		j = 2;
		break;
	default:
		throw new exception("Position invalid");
		break;
	}

	if (_board[i][j] == NULL) {
		_board[i][j] = player;
		return true;
	}
	else {
		cout << "Choose another place" << endl;
		return false;
	}
}

bool TicTacToe::has_winner()
{
	int player = 2;
	bool hasWinner = true;
	while (player > 0)
	{
		// rows
		for (int i = 0; i < _boardSize; i++)
		{
			hasWinner = true;
			for (int j = 0; j < _boardSize; j++)
			{
				if (_board[i][j] != player) {
					hasWinner = false;
					break;
				}
			}

			if (hasWinner) {
				cout << "Congratulations!!! The Player " << player << " won!" << endl;
				return true;
			}
		}

		// columns
		for (int i = 0; i < _boardSize; i++)
		{
			hasWinner = true;
			for (int j = 0; j < _boardSize; j++)
			{
				if (_board[j][i] != player) {
					hasWinner = false;
					break;
				}
			}

			if (hasWinner) {
				cout << "Congratulations!!! The Player " << player << " won!" << endl;
				return true;
			}
		}

		if ((_board[0][0] == player && _board[1][1] == player && _board[2][2] == player) ||
			(_board[0][2] == player && _board[1][1] == player && _board[2][0] == player)) {
			cout << "Congratulations!!! The Player " << player << " won!" << endl;
			return true;
		}

		player--;
	}

	return false;
}

int TicTacToe::chances_to_win(int** state, int player)
{
	int chances = 0;
	bool opportunityToWin = true;

	// rows
	for (int i = 0; i < _boardSize; i++)
	{
		opportunityToWin = true;
		for (int j = 0; j < _boardSize; j++)
		{
			if ((state[i][j] != player && state[i][j] != NULL) || (state[i][0] == NULL && state[i][1] == NULL && state[i][2] == NULL)) {
				opportunityToWin = false;
				break;
			}
		}

		if (opportunityToWin) {
			chances++;
		}
	}

	// columns
	for (int j = 0; j < _boardSize; j++)
	{
		opportunityToWin = true;
		for (int i = 0; i < _boardSize; i++)
		{
			if (state[i][j] != player && state[i][j] != NULL || (state[0][j] == NULL && state[1][j] == NULL && state[2][j] == NULL)) {
				opportunityToWin = false;
				break;
			}
		}

		if (opportunityToWin) {
			chances++;
		}
	}

	if (!(state[0][0] == NULL && state[1][1] == NULL && state[2][2] == NULL)) {
		if (((state[0][0] == player || state[0][0] == NULL) && (state[1][1] == player || state[1][1] == NULL) && (state[2][2] == player || state[2][2] == NULL))) {
			chances++;
		}
	}

	if (!(state[0][2] == NULL && state[1][1] == NULL && state[2][0] == NULL)) {
		if ((state[0][2] == player || state[0][2] == NULL) && (state[1][1] == player || state[1][1] == NULL) && (state[2][0] == player || state[2][0] == NULL)) {
			chances++;
		}
	}

	return chances;
}

bool TicTacToe::compare(int ** first, int ** second)
{
	for (int i = 0; i < this->_boardSize; i++)
	{
		for (int j = 0; j < this->_boardSize; j++)
		{
			if (first[i][j] != second[i][j]) {
				return false;
			}
		}
	}

	return true;
}

int TicTacToe::manhattan_distance(int ** test, int ** goal)
{
	return 0;
}

int TicTacToe::utility_function(int ** state)
{
	return 0;
}

int ** TicTacToe::minimax(int ** content, int levels)
{
	this->root = new TreeNode<int**>(content, NULL, 0, 0, this->new_id());
	this->root->level = 0;
	this->stack_minimax_list->clear();
	this->queue_minimax_list->clear();
	this->stack_minimax_list->push(this->root);
	this->queue_minimax_list->enqueue(this->root);

	TreeNode<int**>* ptr = NULL;
	int bestScore = -99999;
	int** bestState = NULL;
	SimpleNode<TreeNode<int**>*>* ptrList = NULL;

	// creating nodes
	while (!this->queue_minimax_list->is_empty())
	{
		ptr = this->queue_minimax_list->dequeue();
		this->create_children_nodes(ptr, ptr->level % 2 == 0 ? 2 : 1, levels);

		if (ptr->has_children()) {
			SimpleNode<TreeNode<int**>*>* child = ptr->children_nodes->get_root();

			while (child != NULL)
			{
				if (child->content->level < levels) {
					this->stack_minimax_list->push(child->content);
					this->queue_minimax_list->enqueue(child->content);
				}
				child = child->next_node;
			}
		}
	}

	ptr = NULL;
	ptrList = NULL;

	// calculating score
	while (!this->stack_minimax_list->is_empty())
	{
		ptr = this->stack_minimax_list->pop();
		if (ptr->parent == NULL || !ptr->parent->has_child_to_explore())
			continue;

		ptrList = ptr->parent->children_nodes->get_root();
		if (ptr->level == levels - 1) { // for the leaves
			while (ptrList != NULL)
			{
				ptrList->content->u_score = chances_to_win(ptrList->content->content, 2) - chances_to_win(ptrList->content->content, 1);
				ptrList->content->explored = true;
				ptrList = ptrList->next_node;
			}
		}
		else {
			SimpleNode<TreeNode<int**>*>* aux = ptrList;
			if (ptr->level % 2 == 0) { // to maximize
				while (aux != NULL)
				{
					if (aux->next_node != NULL && aux->content->u_score > aux->next_node->content->u_score) {
						ptr->u_score = aux->content->u_score;
					}
					aux = aux->next_node;
				}
			}
			else { // to minimize
				while (aux != NULL)
				{
					if (aux->next_node != NULL && aux->content->u_score < aux->next_node->content->u_score) {
						ptr->u_score = aux->content->u_score;
					}
					aux = aux->next_node;
				}
			}
		}
	}

	this->print_node_children(this->root);

	// checking best state	
	ptr = this->root;
	ptrList = NULL;
	if (ptr->has_children()) {
		ptrList = ptr->children_nodes->get_root();
		while (ptrList->next_node != NULL)
		{
			if (ptrList->content->u_score > bestScore) {
				bestState = ptrList->content->content;
			}
			ptrList = ptrList->next_node;
		}
	}

	return bestState;
}

void TicTacToe::create_children_nodes(TreeNode<int**>* node, int player, int maxLevel)
{
	TreeNode<int**>* newState = NULL;
	bool search_zero = false;
	int i = 0;
	int j = 0;

	if (node == NULL)
		throw CustomException("create_children_nodes - node is null or empty");

	for (i = 0; i < this->_boardSize; i++)
	{
		for (j = 0; j < this->_boardSize; j++)
		{
			if (node->content[i][j] == NULL && node->level < maxLevel) {
				newState = this->get_copy_node(node);
				newState->content[i][j] = player;
				newState->parent = node;
				this->set_child_properties(newState, NULL);
				node->children_nodes->enqueue(newState);
			}
		}
	}
}

TreeNode<int**>* TicTacToe::get_copy_node(TreeNode<int**>* node)
{
	int** copy = new int*[this->_boardSize];

	for (int i = 0; i < this->_boardSize; i++)
	{
		copy[i] = new int[this->_boardSize];

		for (int j = 0; j < this->_boardSize; j++)
		{
			copy[i][j] = node->content[i][j];
		}
	}

	TreeNode<int**>* newNode = new TreeNode<int**>(copy, node, 0);
	newNode->level = node->level;

	return newNode;
}
