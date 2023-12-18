#include "pch.h"
#include "TestClass.h"

TestClass::TestClass():mstr("Bye\n\0")
{
}

TestClass::~TestClass()
{
}

void TestClass::Initialize()
{
	printf("%s\n", mstr);
}

void TestClass::Release()
{
	delete testInst;
}

