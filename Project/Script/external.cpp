#include "pch.h"
#include "external.h"
#include "ScriptManager.h"

SCRIPTDLL_DECLSPEC void CreateManager()
{
    return MCreate(Script::ScriptManager);
}

SCRIPTDLL_DECLSPEC void DestroyManager()
{
    return MDestroy(Script::ScriptManager);
}

SCRIPTDLL_DECLSPEC IManager* GetManagerInstance()
{
    return GetInst(Script::ScriptManager);
}
