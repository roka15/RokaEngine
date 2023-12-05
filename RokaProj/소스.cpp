#include <Windows.h>
#include <crtdbg.h>

#include "..\\GenericLib\\interface.h"

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//GenericManager* ptr = GetMGenericInst();
	
	
	HMODULE testDll = LoadLibrary(L"..\\External\\Dll\\GenericLib.dll");
	if (testDll == NULL)
		int a = 0;

	
	MTestClass_PFUNC testfunc = (MTestClass_PFUNC)GetProcAddress(testDll, "GetMTestClassInst");
	IManager* testptr = testfunc();
	testptr->Print();
	MGeneric_PFUNC func = (MGeneric_PFUNC)GetProcAddress(testDll, "GetMGenericInst");
	IManager* ptr = func();
	ptr->Print();

	testptr->Destroy();
	ptr->Destroy();
	
	
	FreeLibrary(testDll);
	return 0;
}