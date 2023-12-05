#pragma once
#include "interface.h"

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

#define SINGLETON(ctype)private: ctype();~ctype();\
private: static ctype* minstance;\
public:  static ctype* GetInst();


class DLL_DECLSPEC GenericManager : public IManager
{
	SINGLETON(GenericManager)
public:
	virtual void Print()override;
	virtual void Destroy()override;
private:

};




