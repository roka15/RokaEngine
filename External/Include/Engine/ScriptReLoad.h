#pragma once
#include <RokaSTL/SingleTon.h>
#include <RokaSTL/FileManager.h>

namespace RKEngine
{
	class CRKEngine;
	typedef rokaStl::FileTimeStempMap FileTimeStempMap;
	class CScriptReLoad 
	{
		CScriptReLoad(CRKEngine* _engine);
		~CScriptReLoad();
		friend class CRKEngine;
	public:
		bool TimeStempMonitor();
		void ScriptsCompile();
	private:
		CRKEngine* m_Engine;
		FileTimeStempMap mScriptMap;
		TCHAR mScriptPath[MAXPATH];
		std::vector<const TCHAR*> mvecExtensions;
	};

}

