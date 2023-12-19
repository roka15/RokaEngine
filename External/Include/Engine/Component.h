#pragma once
#include "Entity.h"
#include "GameObject.h"
#ifdef CREATEDLL_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS

#define GetOwnerComponentFunc(type) C##type* type(){return m_Owner->type();}
enum class EComponentType;
class DLL_DECLSPEC CComponent : public CEntity
{
private:
	CGameObject* m_Owner;
	const EComponentType m_ComType;
public:
	CComponent(EComponentType _type);
	CComponent(const CComponent& _ref);
	virtual ~CComponent();

public:
	virtual void Start()=0;
	virtual void Update()=0;
	virtual void LateUpdate()=0;

public:
	virtual void SaveToSceneMetaFile()=0;
	virtual void LoadToSceneMetaFile()=0;

public:
	virtual CComponent* Copy() = 0;
public:
	const EComponentType& GetType() { return m_ComType; }
	CGameObject* GetOwner() { return m_Owner; }
	GetOwnerComponentFunc(Transform);

	friend class CGameObject;
};

