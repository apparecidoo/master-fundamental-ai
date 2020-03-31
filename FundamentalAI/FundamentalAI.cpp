#include "pch.h"
#include <iostream>
#include <functional>

#include "custom_exception.h"
#include "linked_list.h"
#include "stack.h"
#include "stack_dynamic.h"
#include "queue.h"
#include "queue_dynamic.h"
#include "puzzle.h"
#include "jar.h"
#include "tic_tac_toe.h"

using namespace std;
using namespace std::placeholders;

int main()
{
	TicTacToe* test = new TicTacToe(2);

	test->start();

	system("pause");

	return 0;
}