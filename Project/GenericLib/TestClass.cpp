#include "pch.h"
#include "TestClass.h"

TestClass::TestClass():mstr("Bye\n\0")
{
}

TestClass::~TestClass()
{
}

void TestClass::Print()
{
	printf("%s", mstr);
}

void TestClass::Destroy()
{
	delete testInst;
}

