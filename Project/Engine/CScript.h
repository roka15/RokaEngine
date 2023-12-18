#pragma once
#include "pch.h"


#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

class DLL_DECLSPEC CScript
{
public:
	CScript();
	virtual ~CScript();
	virtual void Print();
private:
};

