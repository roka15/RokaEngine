#pragma once
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
	class CMesh;
	class CGraphicsShader;
	class DLL_DECLSPEC CResourceManager:public rokaStl::IManager, public rokaStl::Singleton<CResourceManager>
	{
		SINGLETON(CResourceManager)
		MANAGER
		typedef rokaStl::RBT<const TCHAR*, General::SPtr<General::CResource>> ResMap;
	private:
		ResMap mResourceMap[TYPETOINT(EResourceType::MAX)];
	private:
		void InitMesh();
		void InitShader();
	public:
		template<typename T>
		General::SPtr<T> FindRes(const TCHAR* _resName);
		template<typename T>
		void AddRes(const TCHAR* _resName, General::SPtr<T> _Resource);
	};
	template<> General::SPtr<CMesh> CResourceManager::FindRes(const TCHAR* _resName);
	template<> General::SPtr<CGraphicsShader> CResourceManager::FindRes(const TCHAR* _resName);
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CMesh> _Resource);
	template<> void CResourceManager::AddRes(const TCHAR* _resName, General::SPtr<CGraphicsShader> _Resource);

}


