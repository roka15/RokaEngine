#pragma once

namespace rokaStl
{
	typedef RBT<const TCHAR*, TCHAR*, PTCharEqual, PTCharGreater, PTCharLess> FileTimeStempMap;

	class FileData
	{
	public:
		FileData() 
		{
			int a = 0;
		}
		FileData(const FileData& _ref): m_col(_ref.m_col),m_lineData(_ref.m_lineData)
		{
			int a = 0;
		}
		FileData& operator=(const FileData& _ref)
		{
			m_col = _ref.m_col;
			m_lineData = _ref.m_lineData;
			return *this;
		}
		UINT m_col;
		TCHAR** m_lineData;
	};
	typedef FileData FILEDATA;
#ifdef UNICODE
	typedef wstringstream STRSTREAM;
	typedef wstring TString;
	typedef wifstream INPUT_FILE_STREAM;
	typedef wofstream OUTPUT_FILE_STREAM;
#else
	typedef stringstream STRSTREAM;
	typedef string TString;
	typedef ifstream INPUT_FILE_STREAM;
	typedef ofstream OUTPUT_FILE_STREAM;
#endif
	class FileManager : public Singleton<FileManager>
	{
		SINGLETON(FileManager)
	private:
		TCHAR m_ResourcePath[MAXPATH];
		TCHAR m_IncludePath[MAXPATH];
		TCHAR m_ProjectPath[MAXPATH];
		TCHAR m_SolutionPath[MAXPATH];
		TCHAR m_FileName[MAXPATH];
		TCHAR m_ShaderCodePath[MAXPATH];

		TCHAR m_FileExtension[MAXEXTEN];
		TCHAR m_TimeStemp[MAXPATH];
	public:
		//file
		FILEDATA* ReadFile(EFilePathType _ePath, const TCHAR* _tcPath);
		FILEDATA* ReadHeaderFileNameList(EFilePathType _ePath, const TCHAR* _tcPath);
		bool WriteFile(EFilePathType _ePath,const TCHAR* _tcPath, STRSTREAM& _sstream);
		void FreeFileDetail(FILEDATA*& _file);
		//path
		const TCHAR* GetResourcePath();
		const TCHAR* GetIncludePath();
		const TCHAR* GetProjectPath();
		const TCHAR* GetSolutionPath();
		const TCHAR* GetFileName(const TCHAR* _path);
		const TCHAR* GetShaderCodePath();
		const TCHAR* GetFileExtension(const TCHAR* _path);
		const TCHAR* GetTimeStemp(const TCHAR* _path);
		const TCHAR* GetPath(EFilePathType _ePath);
		
		void ReadFileTimeStemp(FileTimeStempMap& _map,const TCHAR* _path,std::vector<const TCHAR*> _extensions);
	private:
		void SetSolutionPath();
		void SetPath(TCHAR* _Outsave,const TCHAR* _path);
		TString CatPath(EFilePathType _ePath, const TCHAR* _path);
	};
}


