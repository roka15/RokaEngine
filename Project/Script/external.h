#pragma once
#include "pch.h"
#include <RokaSTL/interface.h>

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

using namespace rokaStl;

typedef void (*M_ScriptLife_PFUNC)();
typedef IManager* (*M_ScriptGetInst_PFUNC)();

extern "C"
{
	DLL_DECLSPEC void CreateManager();
	DLL_DECLSPEC void DestroyManager();
	DLL_DECLSPEC IManager* GetManagerInstance();
}