#include "pch.h"
#include "interface.h"
#include "GenericManager.h"
#include "TestClass.h"
//#include "..\\External\\Include\\globalClass.h"
IManager* testInst = nullptr;
DLL_DECLSPEC IManager* GetMGenericInst()
{
	return GenericManager::GetInst();
}

DLL_DECLSPEC IManager* GetMTestClassInst()
{
	testInst = new TestClass();
	return testInst;
}
//template<>
//DLL_DECLSPEC MyClass& Singleton<MyClass>::Instance()
//{
//	static MyClass instance;
//	return instance;
//}