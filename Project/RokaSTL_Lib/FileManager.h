#pragma once

namespace rokaStl
{
	class FileManager : public Singleton<FileManager>
	{
		SINGLETON(FileManager)
	private:
		TCHAR m_ResourcePath[MAXPATH];
		TCHAR m_IncludePath[MAXPATH];
		TCHAR m_ProjectPath[MAXPATH];
		TCHAR m_SolutionPath[MAXPATH];
		TCHAR m_FileName[MAXPATH];
		TCHAR m_FileExtension[MAXPATH];
	
	public:
		//file

		//path
		TCHAR* GetResourcePath();
		TCHAR* GetIncludePath();
		TCHAR* GetProjectPath();
		TCHAR* GetSolutionPath();
		TCHAR* GetFileName(std::string& _spath);
		TCHAR* GetFileExtension(std::string& _spath);
	};
}


