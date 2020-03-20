#include <iostream>
#include <string.h>

#ifndef JAR_NODE_H
#define JAR_NODE_H

using namespace std;

class JarNode
{
public:
	JarNode();
	JarNode(int jarA, int jarB, string operation = "");
	int jarA;
	int jarB;
	string operation;
};

#endif
