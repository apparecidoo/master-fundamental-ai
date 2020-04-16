#include "pch.h"
#include "jar_content.h"

JarContent::JarContent()
{
}

JarContent::JarContent(int jarA, int jarB, string operation)
{
	this->jarA = jarA;
	this->jarB = jarB;
	this->operation = operation;
}
