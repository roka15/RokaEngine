#include "pch.h"

typedef rokaStl::RBT<const TCHAR*, TCHAR*, PTCharEqual, PTCharGreater, PTCharLess>  rokaMap;

rokaMap TimeStempMap;
TCHAR scriptPath[MAXPATH] = {};

void AssignmentTCHAR(TCHAR*& _origin, const TCHAR* _change)
{
	size_t len = _tcslen(_origin);
	memset(_origin, 0, len);

	_tcscpy(_origin, _change);
}
void ReadFileTimeStemp(rokaMap& _map, const TCHAR* _path)
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
bool ReWriteTimeStempCheck(rokaMap& _origin)
{
	rokaMap ReTimeStemp;
	ReTimeStemp.innerClear();
	ReadFileTimeStemp(ReTimeStemp, scriptPath);

	size_t originSize = _origin.size();
	size_t ReLoadSize = ReTimeStemp.size();

	if (originSize != ReLoadSize)
	{
		ReTimeStemp.clear();
		return true;
	}
		
	rokaStl::Iterator<const TCHAR*, TCHAR*>::MapIterator itr = _origin.begin();
	for (; itr != _origin.end(); itr++)
	{
		const TCHAR*  key = itr.GetKey();
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


int main()
{
	MemoryLeakCheck
	rokaStl::FileManager::Create();

	rokaStl::FileManager* file = M_FILE;

	TimeStempMap.innerClear();

	_tcscpy(scriptPath, M_FILE->GetProjectPath());
	_tcscat(scriptPath, TEXT("\\Script"));

	ReadFileTimeStemp(TimeStempMap, scriptPath);

	TCHAR* TimeStemp = TimeStempMap[(TCHAR*)TEXT("CTestScript.h")];
	AssignmentTCHAR(TimeStemp, TEXT("ChangeTest"));
	

	bool flag = ReWriteTimeStempCheck(TimeStempMap);
	
	if (flag)
		cout << "º¯È­ °¨Áö µÊ." << endl;

	TimeStempMap.clear();

	rokaStl::FileManager::Destroy();
}