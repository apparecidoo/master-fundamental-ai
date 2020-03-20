#include "pch.h"
#include "jar_node.h"

JarNode::JarNode()
{
}

JarNode::JarNode(int jarA, int jarB, string operation)
{
	this->jarA = jarA;
	this->jarB = jarB;
	this->operation = operation;
}
