#include "pch.h"
#include "FileManager.h"

namespace General
{
	FileManager::FileManager()
		: m_ProjectPath(),
		m_ResourcePath(),
		m_IncludePath(),
		m_SolutionPath(),
		m_FileName(),
		m_FileExtension()
	{
		ZeroMemory(m_ProjectPath, MAXPATH);
		ZeroMemory(m_ResourcePath, MAXPATH);
		ZeroMemory(m_IncludePath, MAXPATH);
		ZeroMemory(m_SolutionPath, MAXPATH);
		ZeroMemory(m_ShaderCodePath, MAXPATH);

		SetSolutionPath();
		SetPath(m_ProjectPath, TEXT("\\Project"));
		SetPath(m_IncludePath, TEXT("\\OutputFile\\Content"));
		SetPath(m_ResourcePath, TEXT("\\External\\Include"));
		SetPath(m_ShaderCodePath, TEXT("\\Project\\Renderer"));
	}
	FileManager::~FileManager()
	{
	}



	FILEDATA* FileManager::ReadFile(EFilePathType _ePath, const TCHAR* _tcPath)
	{
		FILEDATA* result = nullptr; 
		
		TString Path = CatPath(_ePath, _tcPath);
#pragma region read file
		std::vector<TCHAR> vecWords;
		std::vector<TCHAR*> vecStrs;
		INPUT_FILE_STREAM readFile;

		TCHAR word;
		readFile.open(Path);
		if (readFile.is_open())
		{
			result = new FILEDATA();
			while (readFile.eof() == false)
			{
				word = readFile.get();
				if (word == '\n')
				{
					size_t wordLen = vecWords.size()+1;
					if (wordLen == 1)
						continue;
					TCHAR* tempPtr = new TCHAR[wordLen]();
					memcpy(tempPtr,vecWords.data(), wordLen * STR_LENGTH_MULTIPLIER);
					tempPtr[wordLen - 1] = '\0';
					vecStrs.push_back(tempPtr);
					vecWords.clear();
					continue;
				}
				vecWords.push_back(word);
			}

			UINT iCol = vecStrs.size();
			result->m_col = iCol;
			UINT iRow = 0;
			result->m_lineData = new TCHAR * [iCol];
			for (int i = 0; i < iCol; ++i)
			{
				result->m_lineData[i] = vecStrs[i];
			}
#pragma endregion

			readFile.close();
		}

		return result;
	}

	FILEDATA* FileManager::ReadHeaderFileNameList(EFilePathType _ePath, const TCHAR* _tcPath)
	{
		FILEDATA* result = new FILEDATA();
		const TCHAR* FirstPath = GetPath(_ePath);
		const TCHAR* SecondPath = _tcPath;
		TCHAR Path[MAXPATH]={};
		_tcscpy(Path, FirstPath);
		_tcscat(Path, SecondPath);

		std::vector<TCHAR*> vecFile;
		for (const auto& entry : directory_iterator(Path))
		{
			if (is_regular_file(entry.path()))
			{
				TCHAR entryPath[MAXPATH]{};

#ifdef UNICODE
				_tcscpy(entryPath, entry.path().wstring().c_str());
#else
				_tcscpy(entryPath, entry.path().string().c_str());
#endif
				const TCHAR* tcExtension = M_FILE->GetFileExtension(entryPath);
				if (_tcscmp(tcExtension, TEXT(".h")) == 0)
				{
					TCHAR* tcFileName = new TCHAR[MAXPATH]();
					ZeroMemory(tcFileName, MAXPATH);
					_tcscpy(tcFileName, M_FILE->GetFileName(entryPath));
					
					vecFile.push_back(tcFileName);
				}
			}
		}
		
		const UINT iCol = vecFile.size();
		result->m_col = iCol;
		result->m_lineData = new TCHAR*[iCol];
		for (int i = 0; i < iCol; ++i)
		{
			result->m_lineData[i] = vecFile[i];
		}

		return result;
	}

	bool FileManager::WriteFile(EFilePathType _ePath, const TCHAR* _tcPath, STRSTREAM& _sstream)
	{

		OUTPUT_FILE_STREAM writeFile;
		TString Path = CatPath(_ePath, _tcPath);
		writeFile.open(Path);
		TString str;
		
		while (_sstream.good())
		{
			getline(_sstream, str, TEXT('\n'));
			str.append(TEXT("\n"));
			writeFile.write(str.c_str(),str.size());
		}
		writeFile.close();
		return false;
	}

	void FileManager::FreeFileDetail(FILEDATA*& _file)
	{
		if (_file->m_lineData != nullptr)
		{
			for (int i = 0; i < _file->m_col; ++i)
			{
				delete[] _file->m_lineData[i];
				_file->m_lineData[i] = nullptr;
			}
			delete[](_file->m_lineData);
			_file->m_lineData = nullptr;
		}
		delete _file;
		_file = nullptr;
	}

	const TCHAR* FileManager::GetResourcePath()
	{
		return m_ResourcePath;
	}

	const TCHAR* FileManager::GetIncludePath()
	{
		return m_IncludePath;
	}

	const TCHAR* FileManager::GetProjectPath()
	{
		return m_ProjectPath;
	}

	const TCHAR* FileManager::GetSolutionPath()
	{
		return m_SolutionPath;
	}

	const TCHAR* FileManager::GetFileName(const TCHAR* _path)
	{
		ZeroMemory(m_FileName, MAXPATH);
		_tsplitpath_s(_path,NULL,0,NULL,0,m_FileName,MAXPATH,NULL,0);
		return m_FileName;
	}

    const TCHAR* FileManager::GetShaderCodePath()
    {
        return m_ShaderCodePath;
    }

	const TCHAR* FileManager::GetFileExtension(const TCHAR* _path)
	{
		ZeroMemory(m_FileExtension, MAXEXTEN);
		_tsplitpath_s(_path, NULL, 0, NULL, 0, nullptr, 0, m_FileExtension,MAXEXTEN);
		return m_FileExtension;
	}

	const TCHAR* FileManager::GetTimeStemp(const TCHAR* _path)
	{
		ZeroMemory(m_TimeStemp, MAXPATH);
		const file_time_type last_update = last_write_time(_path);
		std::time_t last_timestemp_t = decltype(last_update)::clock::to_time_t(last_update);
		_tasctime_s(m_TimeStemp, std::localtime(&last_timestemp_t));
		return m_TimeStemp;
	}

	const TCHAR* FileManager::GetPath(EFilePathType _ePath)
	{
		switch (_ePath)
		{
		case EFilePathType::SOLUTION:
			return m_SolutionPath;
			break;
		case EFilePathType::PROJECT:
			return m_ProjectPath;
			break;
		case EFilePathType::INCLUDE:
			return m_IncludePath;
			break;
		case EFilePathType::RESOURCE:
			return m_ResourcePath;
			break;
		}
	}

    void FileManager::ReadFileTimeStemp(FileTimeStempMap& _map, const TCHAR* _path,std::vector<const TCHAR*> _extensions)
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
				const TCHAR* sExtension = GetFileExtension(entryPath);
				size_t size = _extensions.size();
				for (int i = 0; i < size; ++i)
				{
					if (_tcscmp(sExtension, _extensions[i]) == 0)
					{
						TCHAR* sFileName = new TCHAR[MAXPATH]();
						ZeroMemory(sFileName, MAXPATH);
						_tcscpy(sFileName, GetFileName(entryPath));
						_tcscat(sFileName, sExtension);

						TCHAR* sTimeStemp = new TCHAR[MAXPATH]();
						_tcscpy(sTimeStemp, GetTimeStemp(entryPath));

						_map.insert(std::make_pair((TCHAR*)sFileName, (TCHAR*)sTimeStemp));
					}
				}
			}
		}
    }

	void FileManager::SetSolutionPath()
	{
		::GetCurrentDirectory(MAXPATH, m_SolutionPath);

		size_t solution_len = _tcslen(m_SolutionPath);
		size_t slash_cnt = 0;
		const size_t slash_max = 2;
		size_t solution_index = 0;
		while (1)
		{
			if (slash_cnt >= slash_max)
				break;

			TCHAR* pcSlash = _tcsrchr(m_SolutionPath, TEXT('\\'));
			solution_index = pcSlash - m_SolutionPath;
			if (pcSlash == nullptr)
			{
				Assert(pcSlash != nullptr, "FileManager() : solution path error");
				return;
			}
			else
			{
				++slash_cnt;
				for (int i = solution_index; i < solution_len; ++i)
				{
					m_SolutionPath[i] = TEXT('\0');
				}
				solution_len = solution_index;
			}
		}
	}

	void FileManager::SetPath(TCHAR* _Outsave,const TCHAR* _path)
	{
		size_t solutionLen = _tcslen(m_SolutionPath);
		TCHAR tempPath[MAXPATH];
		memset(tempPath, 0, MAXPATH);

		_tcscpy(tempPath, m_SolutionPath);
		_tcscat(tempPath, _path);
		_tcscpy(_Outsave, tempPath);
	}
	TString FileManager::CatPath(EFilePathType _ePath, const TCHAR* _path)
	{
		const TCHAR* FirstPath = GetPath(_ePath);
		const TCHAR* SecondPath = _path;
		TCHAR Path[MAXPATH] = {};
		_tcscpy(Path, FirstPath);
		_tcscat(Path, SecondPath);

		TString result(Path);
		return result;
	}

}
