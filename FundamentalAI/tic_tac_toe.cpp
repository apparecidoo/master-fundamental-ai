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
	print_content(_board);
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

bool TicTacToe::compare(int ** first, int ** second)
{
	return false;
}

int TicTacToe::manhattan_distance(int ** test, int ** goal)
{
	return 0;
}

int TicTacToe::utility_function(int ** state)
{
	return 0;
}
