#include "pch.h"
#include "ScriptManager.h"
#include "CTestScript.h"
ScriptManager::ScriptManager()
{
}
ScriptManager::~ScriptManager()
{
}
void  ScriptManager::Initialize()
{
}
void ScriptManager::Loop()
{
}
void ScriptManager::Release()
{
}
void ScriptManager::GetScriptsInfo(wchar_t** _vec)
{
}
CScript* ScriptManager::GetScript(unsigned int _ScriptType)
{
    std::cout << " new Script Test" << std::endl;
    EScriptType eType = (EScriptType)_ScriptType;
    switch (eType)
    {
    case EScriptType::TEST:
        return new CTestScript(_ScriptType);
        break;
    }
    return nullptr;
}

CScript* ScriptManager::GetScript(const wchar_t* _ScriptName)
{
    return nullptr;
}

const wchar_t* ScriptManager::GetScriptName(CScript* _pScript)
{
    return nullptr;
}

SCRIPTDLL_DECLSPEC void ScriptManagerCreate()
{
    return MCreate(ScriptManager);
}

SCRIPTDLL_DECLSPEC void ScriptManagerDestory()
{
    return MDestroy(ScriptManager);
}

SCRIPTDLL_DECLSPEC ScriptManager* GetScriptManager()
{
    return GetInst(ScriptManager);
}
