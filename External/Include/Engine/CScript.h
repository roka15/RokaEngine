#pragma once
#include "pch.h"
#include "Component.h"
#include "components.h"

#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

enum class DLL_DECLSPEC EScriptParam
{
	INT,
	FLOAT,
	DOUBLE,
	VEC2,
	VEC3,
	VEC4
};
struct tScriptParam
{
	unsigned int etype;
	void* pData;
	const char* pDesc;
};
class DLL_DECLSPEC CScript : public CComponent
{
private:
	unsigned int m_ScriptType;
	std::vector<tScriptParam> m_ScriptParams;
public:
	CScript(unsigned int _type);
	CScript(const CScript& _ref);
	virtual ~CScript();
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void SaveToSceneMetaFile() = 0;
	virtual void LoadToSceneMetaFile() = 0;
public:
	virtual void LateUpdate()final {};

	virtual void OnCollisionEnter(CCollider3D* _other) {}
	virtual void OnCollisionStay(CCollider3D* _other) {}
	virtual void OnCollisionExit(CCollider3D* _other) {}
	virtual CScript* Copy() = 0;
protected:
	//Add Script Param 함수를 만든다. 나중에 im gui 에서 쓸것.
public:
	const unsigned int& GetScriptType() { return m_ScriptType; }
	virtual void Print();
private:
};

