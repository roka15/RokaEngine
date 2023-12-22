#include "pch.h"
#include "FileManager.h"

namespace rokaStl
{
    FileManager::FileManager()
        : m_ProjectPath(TEXT("..\\")),
          m_ResourcePath(TEXT("..\\..\\OutputFile\\Content\\")),
          m_IncludePath(TEXT("..\\..\\External\\Include\\")),
          m_SolutionPath(),
          m_FileName(),
          m_FileExtension()
    {
        ::GetCurrentDirectory(MAXPATH,m_SolutionPath);

        m_ResourcePath
    }
    FileManager::~FileManager()
    {

    }

  

    std::string FileManager::GetResourcePath()
    {
        return m_ResourcePath;
    }

    std::string FileManager::GetIncludePath()
    {
        return m_IncludePath;
    }

    std::string FileManager::GetProjectPath()
    {
        return m_ProjectPath;
    }

    std::string FileManager::GetSolutionPath()
    {
        return std::string();
    }

    std::string FileManager::GetFileName(std::string& _spath)
    {
        return std::string();
    }

    std::string FileManager::GetFileExtension(std::string& _spath)
    {
        return std::string();
    }

}
