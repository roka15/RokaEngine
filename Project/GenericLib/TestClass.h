#pragma once
#include "interface.h"

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS


class TestClass : public IManager
{
public:
	TestClass();
	 ~TestClass();
	virtual void Print()override;
	virtual void Destroy()override;
private:
	const char mstr[50];
};



