#include <iostream>
#include <string.h>

#ifndef JAR_CONTENT_H
#define JAR_CONTENT_H

using namespace std;

class JarContent
{
public:
	JarContent();
	JarContent(int jarA, int jarB, string operation = "");
	int jarA;
	int jarB;
	string operation;
};

#endif
