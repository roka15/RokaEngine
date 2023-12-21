#pragma once
#include "interface.h"

namespace rokaStl
{
	class CDllLoader :public IManager, public Singleton<CDllLoader>
	{
		SINGLETON(CDllLoader)
		MANAGER
	private:
		std::vector<HMODULE> m_Dlls;
		std::vector<std::wstring> m_DllPaths;
	public:
		bool LoadDll(EDllType _etype);
		void FreeDll(EDllType _etype);
		void SetDllPath(EDllType _etype, std::wstring _path);
		HMODULE& GetDLL(EDllType _etype) { return m_Dlls[TYPETOINT(_etype)]; }
	private:
	};

}

