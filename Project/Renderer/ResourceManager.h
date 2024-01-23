#pragma once
#include "Mesh.h"
#include "CGraphicsShader.h"

#ifdef RENDERER_EXPORTS
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif // CREATEDLL_EXPORTS


namespace General
{
	template<typename T>
	class SPtr;
	class CResource;
}


namespace Renderer
{
	class DLL_DECLSPEC CResourceManager:public rokaStl::IManager, public rokaStl::Singleton<CResourceManager>
	{
		SINGLETON(CResourceManager)
		MANAGER
		typedef rokaStl::RBT<const TCHAR*, General::SPtr<General::CResource>> ResMap;
	private:
		ResMap mResourceMap[TYPETOINT(EResourceType::MAX)];
	private:
		template<typename T>
		EResourceType GetResType();
	public:
		template<typename T>
		General::SPtr<T> FindRes(const TCHAR* _resName);
		template<typename T>
		void AddRes(const TCHAR* _resName, General::SPtr<T> _Resource);
	};

	template<typename T>
	EResourceType CResourceManager::GetResType()
	{
		const type_info& mesh = typeid(CMesh);
		const type_info& graphics_shader = typeid(CGraphicsShader);
		
		const type_info& Ttype = typeid(T);
		if (mesh.hash_code() == Ttype.hash_code())
			return EResourceType::Mesh;
		if (graphics_shader.hash_code() == Ttype.hash_code)
			return EResourceType::GraphicsShader;
	}
	template <typename T>
	General::SPtr<T> CResourceManager::FindRes(const TCHAR* _resName)
	{
		EResourceType eType = GetResType<T>();
		General::SPtr<T> Resource = mResourceMap[TYPETOINT(eType)][_resName];
		return (T*)Resource.get();
	}
	template <typename T>
	void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<T> _Resource)
	{
		EResourceType eType = GetResType<T>();
		General::SPtr<T> Resource = FindRes<T>(_resName);
		if (Resource != nullptr)
			Assert(nullptr, TEXT("ResourceManager AddRes Error! Resource Key ม฿บน"));
	
		mResourceMap[TYPETOINT(eType)].insert(std::make_pair(_resName, _Resource.get()));
	}

	template<> EResourceType CResourceManager::GetResType<CMesh>();
	template<> EResourceType CResourceManager::GetResType<CGraphicsShader>();
	template<> General::SPtr<CMesh> CResourceManager::FindRes(const TCHAR* _resName);
	template<> General::SPtr<CGraphicsShader> CResourceManager::FindRes(const TCHAR* _resName);
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CMesh> _Resource);
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CGraphicsShader> _Resource);

}


