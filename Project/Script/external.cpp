#include "pch.h"
#include "external.h"
#include "ScriptManager.h"

DLL_DECLSPEC void CreateManager()
{
    return MCreate(ScriptManager);
}

DLL_DECLSPEC void DestroyManager()
{
    return MDestroy(ScriptManager);
}

DLL_DECLSPEC IManager* GetManagerInstance()
{
    return GetInst(ScriptManager);
}
