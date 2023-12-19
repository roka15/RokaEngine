#include "pch.h"
#include "external.h"
#include "ScriptManager.h"

SCRIPTDLL_DECLSPEC void CreateManager()
{
    return MCreate(ScriptManager);
}

SCRIPTDLL_DECLSPEC void DestroyManager()
{
    return MDestroy(ScriptManager);
}

SCRIPTDLL_DECLSPEC IManager* GetManagerInstance()
{
    return GetInst(ScriptManager);
}
