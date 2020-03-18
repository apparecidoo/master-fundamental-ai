#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

#ifndef CUSTOM_EXCEPTION_H
#define CUSTOM_EXCEPTION_H

class CustomException : public exception
{
public:
	CustomException(const char* msg);
	void showMessage();
};

#endif