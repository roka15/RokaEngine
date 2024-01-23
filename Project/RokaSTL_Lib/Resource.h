#pragma once
#include "Entity.h"
namespace Renderer
{
	enum class EResourceType;
}
namespace General
{
	class CResource : public CEntity
	{
	private:	
		const Renderer::EResourceType m_eType;
		std::wstring m_strKey;
		std::wstring m_strPath;
		UINT m_uiRefCnt;
		bool m_bEngineRes;
	public:
		CResource(Renderer::EResourceType _eType, bool _bEngine);
		CResource(const CResource& _ref);
		virtual ~CResource();
	public:
		CLASS_NOCOPY(CResource)
		template <typename T>
		friend class SPtr;
	public:
		void SetKey(const wstring& _key) { m_strKey = _key; }
		void SetPath(const wstring& _path) { m_strPath = _path; }
		const wstring& GetKey() { return m_strKey; }
		const wstring& GetPath() { return m_strPath; }
		const Renderer::EResourceType& GetType() { return m_eType; }
		const bool& IsEngineRes() { return m_bEngineRes; }
	private:
		void AddRefCnt() { ++m_uiRefCnt; }
		void Release();

		virtual void UpdateData() {};
	};
}

