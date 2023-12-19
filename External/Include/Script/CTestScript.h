#pragma once
#include "pch.h"
#include <Engine/define.h>
#include <Engine/CScript.h>


#ifdef SCRIPTDLL_EXPORTS
#define SCRIPTDLL_DECLSPEC __declspec(dllexport)
#else
#define SCRIPTDLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

class SCRIPTDLL_DECLSPEC CTestScript : public CScript
{
public:
    CTestScript(unsigned int _type);
    virtual ~CTestScript();

public:
    virtual void Start() { std::cout << "Start()" << std::endl; }
    virtual void Update() { std::cout << "Update()" << std::endl; }
    virtual void SaveToSceneMetaFile() { std::cout << "SaveScene()" << std::endl; }
    virtual void LoadToSceneMetaFile() { std::cout << "LoadScene()" << std::endl; }
    
    CLASS_COPY(CTestScript)

    virtual void Print()override; 
    virtual void SetData(int _data) { a = _data; }
private:
    int a;
};

