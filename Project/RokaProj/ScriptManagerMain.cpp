#include "pch.h"
#include <Script/external.h>
#include <Script/ScriptManager.h>

int main()
{
	MemoryLeakCheck
		//Dll Test
	HMODULE ScriptDll = LoadLibrary(L"..\\..\\External\\Dll\\Debug\\Script\\Script.dll");

	if (ScriptDll == NULL)
	{
		HRESULT result = GetLastError();
		int a = 0;
	}
	/*M_ScriptLife_PFUNC MScriptCreate = (M_ScriptLife_PFUNC)GetProcAddress(ScriptDll, "CreateManager");
	MScriptCreate();

	M_ScriptGetInst_PFUNC MScriptInst = (M_ScriptGetInst_PFUNC)GetProcAddress(ScriptDll, "GetManagerInstance");
	rokaStl::IManager* inst = MScriptInst();

	ScriptManager* MScript = dynamic_cast<ScriptManager*>(inst);
	MScript->Initialize();
	CScript* script = MScript->GetScript(TYPETOINT(EScriptType::TEST));
	script->Print();
	M_ScriptLife_PFUNC MScriptDestroy = (M_ScriptLife_PFUNC)GetProcAddress(ScriptDll, "DestroyManager");
	MScriptDestroy();*/
}