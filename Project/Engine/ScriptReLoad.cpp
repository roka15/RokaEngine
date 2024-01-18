#include "pch.h"
#include "ScriptReLoad.h"
#include "RKEngine.h"

namespace RKEngine
{ 
	CScriptReLoad::CScriptReLoad(CRKEngine* _engine):
		m_Engine(_engine),
		mScriptPath{},
		mvecExtensions{}
	{	
		_tcscpy(mScriptPath, m_Engine->M_File->GetProjectPath());
		_tcscat(mScriptPath, TEXT("\\Script"));

		mvecExtensions.push_back(TEXT(".cpp"));
		mvecExtensions.push_back(TEXT(".h"));

		mScriptMap.innerClear();
		m_Engine->M_File->ReadFileTimeStemp(mScriptMap, mScriptPath, mvecExtensions);
	}
	CScriptReLoad::~CScriptReLoad()
	{
		mScriptMap.clear();
	}
	bool CScriptReLoad::TimeStempMonitor()
	{
		FileTimeStempMap ReTimeStemp;
		ReTimeStemp.innerClear();
		m_Engine->M_File->ReadFileTimeStemp(ReTimeStemp, mScriptPath, mvecExtensions);

		size_t originSize = mScriptMap.size();
		size_t ReLoadSize = ReTimeStemp.size();

		if (originSize != ReLoadSize)
		{
			ReTimeStemp.clear();
			return true;
		}

		rokaStl::Iterator<const TCHAR*, TCHAR*>::MapIterator itr = mScriptMap.begin();
		for (; itr != mScriptMap.end(); itr++)
		{
			const TCHAR* key = itr.GetKey();
			TCHAR* originData = itr.GetData();
			const TCHAR* reData = ReTimeStemp.find(key).GetData();

			if (_tcscmp(originData, reData) == 0)
				continue;
			else
			{
				AssignmentTCHAR(originData, reData);
				ReTimeStemp.clear();
				return true;
			}
		}

		ReTimeStemp.clear();
		return false;
	}
	void CScriptReLoad::ScriptsCompile()
	{
		TCHAR path[255] = {};
		GetCurrentDirectory(255, path);
		int result = system("cd /D D:\\3DRKEngine\\Project\\Script\\build && cmake .. && cmake --build ./ && pause");
		if (result != 0)
			int a = 0;
	}
}