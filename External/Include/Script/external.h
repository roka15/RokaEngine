#pragma once
#include "pch.h"


#ifdef SCRIPTDLL_EXPORTS
#define SCRIPTDLL_DECLSPEC __declspec(dllexport)
#else
#define SCRIPTDLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

using namespace rokaStl;

typedef void (*M_ScriptLife_PFUNC)();
typedef IManager* (*M_ScriptGetInst_PFUNC)();

extern "C"
{
	SCRIPTDLL_DECLSPEC void CreateManager();
	SCRIPTDLL_DECLSPEC void DestroyManager();
	SCRIPTDLL_DECLSPEC IManager* GetManagerInstance();
}