#include "pch.h"
#include "DllLoader.h"

namespace rokaStl
{
    CDllLoader::CDllLoader()
        :m_DllPaths{},
         m_Dlls{}
    {
        UINT iSize = TYPETOINT(EDllType::END);
        m_DllPaths.resize(iSize);
        m_Dlls.resize(iSize);
    }
    CDllLoader::~CDllLoader()
    {

    }
    void CDllLoader::Initialize()
    {
#ifdef _DEBUG
        SetDllPath(EDllType::ENGINE, L"..\\..\\External\\Dll\\Engine\\Debug\\Engine.dll");
        SetDllPath(EDllType::SCRIPT, L"..\\..\\External\\Dll\\Script\\Debug\\Script.dll");
#else
        SetDllPath(EDllType::ENGINE, L"..\\..\\External\\Dll\\Engine\\Release\\Engine.dll");
        SetDllPath(EDllType::SCRIPT, L"..\\..\\External\\Dll\\Script\\Release\\Script.dll");
#endif
    }
    void CDllLoader::Loop()
    {

    }
    void CDllLoader::Release()
    {
        UINT max = TYPETOINT(EDllType::END);
        for (int i = 0; i < max; i++)
        {
            FreeDll((EDllType)i);
        }

        m_Dlls.clear();
    }
    bool CDllLoader::LoadDll(EDllType _etype)
    {
        UINT iType = TYPETOINT(_etype);
        if (m_DllPaths[iType].size() == 0)
        {
            Assert(m_DllPaths[iType].size() != 0, "LoadDll() : path null");
            return false;
        }
        const wchar_t* const path = m_DllPaths[iType].c_str();

        HMODULE h_LoadDll = LoadLibrary(path);
        if (h_LoadDll == NULL)
        {
            std::string errMsg = "LoadDll() : null load " + std::to_string(iType);
            Assert(h_LoadDll != NULL, errMsg.c_str());
            return false;
        }

        switch (_etype)
        {
        case EDllType::ENGINE:
        case EDllType::SCRIPT:
        case EDllType::RENDER:
        case EDllType::SERVER:
            break;
        default:
            return false;
        }

        m_Dlls[iType] = h_LoadDll;

        return true;
    }

    void CDllLoader::FreeDll(EDllType _etype)
    {
        UINT iType = TYPETOINT(_etype);

        HMODULE h_FreeDll = m_Dlls[iType];
        if (h_FreeDll == NULL)
        {
            // std::string errMsg = "FreeDll(): null free " + std::to_string(iType);
            // Assert(h_FreeDll != NULL, errMsg.c_str());
            return;
        }

        FreeLibrary(h_FreeDll);
    }

    void CDllLoader::SetDllPath(EDllType _etype, std::wstring _path)
    {
        UINT iType = TYPETOINT(_etype);
        m_DllPaths[iType] = _path;
    }

}