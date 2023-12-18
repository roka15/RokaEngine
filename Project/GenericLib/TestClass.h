#pragma once
#include "interface.h"

class TestClass : public IManager
{
public:
	TestClass();
	 ~TestClass();
	virtual void Initialize()override;
	virtual void Release()override;
private:
	const char mstr[50];
};



