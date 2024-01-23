#include "pch.h"
#include "ResourceManager.h"

namespace Renderer
{
	CResourceManager::CResourceManager()
	{
		//ResourceMap.InnerClear 하지말것.
	}
	CResourceManager::~CResourceManager()
	{

	}
	void CResourceManager::Initialize()
	{

	}
	void CResourceManager::Release()
	{

	}
	template<> EResourceType CResourceManager::GetResType<CMesh>()
	{
		return EResourceType::Mesh;
	}
	template<> EResourceType CResourceManager::GetResType<CGraphicsShader>()
	{
		return EResourceType::GraphicsShader;
	}
	template<> General::SPtr<CMesh> CResourceManager::FindRes(const TCHAR* _resName)
	{
		EResourceType eType = EResourceType::Mesh;
		General::SPtr<General::CResource> Resource = mResourceMap[TYPETOINT(EResourceType::Mesh)][_resName];
		return (CMesh*)Resource.get();
	}
	template<> General::SPtr<CGraphicsShader> CResourceManager::FindRes(const TCHAR* _resName)
	{
		EResourceType eType = EResourceType::GraphicsShader;
		General::SPtr<General::CResource> Resource = mResourceMap[TYPETOINT(EResourceType::GraphicsShader)][_resName];
		return (CGraphicsShader*)Resource.get();
	}
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CMesh> _Resource)
	{
		EResourceType eType = EResourceType::Mesh;
		General::SPtr<CMesh> Resource = FindRes<CMesh>(_resName);
		if (Resource.get() != nullptr)
			Assert(nullptr, TEXT("ResourceManager AddRes Error! Resource Key 중복"));

		mResourceMap[TYPETOINT(eType)].insert(std::make_pair(_resName, _Resource.get()));
	}
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CGraphicsShader> _Resource)
	{
		EResourceType eType = EResourceType::GraphicsShader;
		General::SPtr<CGraphicsShader> Resource = FindRes<CGraphicsShader>(_resName);
		if (Resource.get() != nullptr)
			Assert(nullptr, TEXT("ResourceManager AddRes Error! Resource Key 중복"));

		mResourceMap[TYPETOINT(eType)].insert(std::make_pair(_resName, _Resource.get()));
	}
}