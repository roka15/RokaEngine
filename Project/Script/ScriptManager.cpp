#include "pch.h"
#include "ScriptManager.h"
//#include "CTestScript.h"
ScriptManager::ScriptManager()
{
}
ScriptManager::~ScriptManager()
{
}
void  ScriptManager::Initialize()
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
    std::cout << "Script.dll Test" << std::endl;
    return nullptr;
   // return new CTestScript();
}

CScript* ScriptManager::GetScript(const wchar_t* _ScriptName)
{
    return nullptr;
}

const wchar_t* ScriptManager::GetScriptName(CScript* _pScript)
{
    return nullptr;
}

DLL_DECLSPEC void ScriptManagerCreate()
{
    return MCreate(ScriptManager);
}

DLL_DECLSPEC void ScriptManagerDestory()
{
    return MDestroy(ScriptManager);
}

DLL_DECLSPEC ScriptManager* GetScriptManager()
{
    return GetInst(ScriptManager);
}
