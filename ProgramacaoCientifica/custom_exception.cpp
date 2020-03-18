#include "pch.h"
#include "custom_exception.h"

CustomException::CustomException(const char* msg) : exception(msg)
{
}

void CustomException::showMessage()
{
	cout << "***Exception error: " << this->what() << endl;
}