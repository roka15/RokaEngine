#include "pch.h"
#include "interface.h"
#include "GenericManager.h"
#include "TestClass.h"
//#include "..\\External\\Include\\globalClass.h"
IManager* testInst = nullptr;

DLL_DECLSPEC void CreateManager(EGenericManagerType type)
{
	switch (type)
	{
	case EGenericManagerType::TYPE1:
		MCreate(GenericManager);
		break;
	case EGenericManagerType::TYPE2:
		GetMTestClassInst();
		break;
	}
}

DLL_DECLSPEC void DestroyManager(EGenericManagerType type)
{
	switch (type)
	{
	case EGenericManagerType::TYPE1:
		MDestroy(GenericManager);
		break;
	case EGenericManagerType::TYPE2:
		delete testInst;
		break;
	}
}

DLL_DECLSPEC IManager* GetManagerInstance(EGenericManagerType type)
{
	//EGenericManagerType eType = (EGenericManagerType)type;

	switch (type)
	{
	case EGenericManagerType::TYPE1:
		return GetInst(GenericManager);
		break;
	case EGenericManagerType::TYPE2:
		return GetMTestClassInst();
		break;
	}
	return nullptr;
}

IManager* GetMTestClassInst()
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