#include "pch.h"
#include "FileManager.h"

namespace rokaStl
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

		SetSolutionPath();
		SetPath(m_ProjectPath, TEXT("\\Project"));
		SetPath(m_IncludePath, TEXT("\\OutputFile\\Content"));
		SetPath(m_ResourcePath, TEXT("\\External\\Include"));
	}
	FileManager::~FileManager()
	{

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
		return nullptr;
	}

	const TCHAR* FileManager::GetFileName(const TCHAR* _path)
	{
		ZeroMemory(m_TimeStemp, MAXPATH);
		_tsplitpath_s(_path,NULL,0,NULL,0,m_FileName,MAXPATH,NULL,0);
		return m_FileName;
	}

	const TCHAR* FileManager::GetFileExtension(const TCHAR* _path)
	{
		ZeroMemory(m_TimeStemp, MAXPATH);
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

	void FileManager::SetPath(TCHAR* _save,const TCHAR* _path)
	{
		size_t solutionLen = _tcslen(m_SolutionPath);
		TCHAR tempPath[MAXPATH];
		memset(tempPath, 0, MAXPATH);

		_tcscpy(tempPath, m_SolutionPath);
		_tcscat(tempPath, _path);
		_tcscpy(_save, tempPath);
	}
}
