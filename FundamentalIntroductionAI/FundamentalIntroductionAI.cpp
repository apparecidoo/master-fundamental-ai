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

using namespace std;
using namespace std::placeholders;

int main()
{
	Jar* exerciseJar = new Jar(new JarNode(), 3, 4);
	exerciseJar->test();

	system("pause");

	return 0;
}