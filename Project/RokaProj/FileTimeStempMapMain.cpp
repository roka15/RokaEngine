#include "pch.h"

typedef rokaStl::RBT<TCHAR*, TCHAR*, PTCharEqual, PTCharGreater, PTCharLess>  rokaMap;


void ReadFileTimeStemp(rokaMap& _map,const TCHAR* _path)
{
	for (const auto& entry : directory_iterator(_path))
	{
		if (is_regular_file(entry.path()))
		{
			TCHAR entryPath[MAXPATH]{};
		
#ifdef UNICODE
			_tcscpy(entryPath, entry.path().wstring().c_str());
#else
			_tcscpy(entryPath, entry.path().string().c_str());
#endif
			const TCHAR* sextension = M_FILE->GetFileExtension(entryPath);
			if (_tcscmp(sextension, TEXT(".cpp")) == 0
			  || _tcscmp(sextension, TEXT(".h")) == 0)
			{
				TCHAR* sFileName = new TCHAR[MAXPATH]();
				ZeroMemory(sFileName, MAXPATH);
				_tcscpy(sFileName, M_FILE->GetFileName(entryPath));
				_tcscat(sFileName, sextension);

				TCHAR* sTimeStemp = new TCHAR[MAXPATH]();
				_tcscpy(sTimeStemp, M_FILE->GetTimeStemp(entryPath));
				
				_map.insert(std::make_pair((TCHAR*)sFileName, (TCHAR*)sTimeStemp));
			}
		}
	}
}
bool ReWriteTimeStempCheck(rokaMap& _map)
{
	return false;
}
rokaMap TimeStempMap;
int main()
{
	MemoryLeakCheck
	rokaStl::FileManager::Create();

	rokaStl::FileManager* file = M_FILE;

	
	rokaMap map;
	map.innerClear();
	TCHAR scriptPath[MAXPATH];
	_tcscpy(scriptPath, M_FILE->GetProjectPath());
	_tcscat(scriptPath, TEXT("\\Script"));

	ReadFileTimeStemp(map, scriptPath);
	ReWriteTimeStempCheck(map);
	TCHAR* TimeStemp = map[(TCHAR*)TEXT("CTestScript.h")];
	map.clear();

	rokaStl::FileManager::Destroy();
}