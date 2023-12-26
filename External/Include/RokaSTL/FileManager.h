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
		TCHAR m_FileExtension[MAXEXTEN];
		TCHAR m_TimeStemp[MAXPATH];
	
	public:
		//file

		//path
		const TCHAR* GetResourcePath();
		const TCHAR* GetIncludePath();
		const TCHAR* GetProjectPath();
		const TCHAR* GetSolutionPath();
		const TCHAR* GetFileName(const TCHAR* _path);
		const TCHAR* GetFileExtension(const TCHAR* _path);
		const TCHAR* GetTimeStemp(const TCHAR* _path);
	private:
		void SetSolutionPath();
		void SetPath(TCHAR* _save,const TCHAR* _path);
	};
}


