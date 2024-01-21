#pragma once
#include "interface.h"

class TestClass : public IManager
{
	MANAGER
public:
	TestClass();
	 ~TestClass();
private:
	const char mstr[50];
};



