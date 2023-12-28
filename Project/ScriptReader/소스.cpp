#pragma comment(lib,"RokaSTL\\RokaSTL_Lib.lib")
#include <CommonInclude.h>

typedef typename rokaStl::FileManager RKFileManager;
#define M_FILE RKFileManager::GetInstance()

int main()
{
	MemoryLeakCheck

	RKFileManager::Create();
	const TCHAR* tcProjPath = M_FILE->GetProjectPath();
	TCHAR tcCppPath[MAXPATH]{};
	_tcscpy(tcCppPath, tcProjPath);
	_tcscat(tcCppPath, TEXT("\\Script\\ScriptManager.cpp"));

	TCHAR tcHeaderPath[MAXPATH]{};
	_tcscpy(tcHeaderPath, tcProjPath);
	_tcscat(tcHeaderPath, TEXT("\\Script\\ScriptManager.h"));


	const TCHAR* tcSolutionPath = M_FILE->GetSolutionPath();
	const TCHAR* tcScriptTxtPath = TEXT("\\OutputFile\\Debug\\ScriptList.txt");
	//excludelist 읽기
	rokaStl::FileData* ExcludeList = M_FILE->ReadFile(EFilePathType::SOLUTION, TEXT("\\ScriptExcludeList.txt"));
	rokaStl::FileData* FileNameList = M_FILE->ReadHeaderFileNameList(EFilePathType::PROJECT, TEXT("\\Script\\"));

	rokaStl::FileData* SaveScriptTxtList = M_FILE->ReadFile(EFilePathType::SOLUTION, tcScriptTxtPath);


	//excludelist 제외한 FileNameList
	std::vector<TCHAR*> vecScriptFileNameList;
	const UINT& ExcludeCnt = ExcludeList->m_col;
	const UINT& FileNameCnt = FileNameList->m_col;

	for (int i = 0; i < FileNameCnt; ++i)
	{
		bool bExcludeFlag = false;
		for (int j = 0; j < ExcludeCnt; ++j)
		{
			if (_tcscmp(FileNameList->m_lineData[i], ExcludeList->m_lineData[j]) == 0)
				bExcludeFlag = true;
		}
		if (bExcludeFlag == false)
			vecScriptFileNameList.push_back(FileNameList->m_lineData[i]);
	}

	const size_t ScriptTypeCnt = vecScriptFileNameList.size();
	bool bWriteFlag = false;
	if (SaveScriptTxtList == nullptr)
	{
		bWriteFlag = true;
	}
	else
	{
		//save script txt list 와 script file name list 를 비교한다.
		//다른 점이 있다면 script manager와 scriptlist.txt 를 수정한다.
		bool bSameFlag = true;
		size_t save_size = SaveScriptTxtList->m_col;
		size_t file_size = vecScriptFileNameList.size();

		if (save_size == file_size)
		{
			for (int i = 0; i < ScriptTypeCnt; ++i)
			{
				if (_tcscmp(SaveScriptTxtList->m_lineData[i], vecScriptFileNameList[i]) != 0)
				{
					bSameFlag = false;
					break;
				}
			}
		}
		else
			bSameFlag = false;
		
		//bSameFlag = CheckSame()

		if (bSameFlag == false)
		{
			bWriteFlag = true;
		}
	}


	if(bWriteFlag == false)
	{
		M_FILE->FreeFileDetail(ExcludeList);
		M_FILE->FreeFileDetail(FileNameList);
		M_FILE->FreeFileDetail(SaveScriptTxtList);

		RKFileManager::Destroy();
		return 0;
	}

#ifdef UNICODE
	wstringstream strStream;
#else
	stringstream strStream;
#endif

	
#pragma region Write ScriptList.txt
	for (int i = 0; i < ScriptTypeCnt; ++i)
	{
		strStream << vecScriptFileNameList[i] << TEXT("\n");
	}

	M_FILE->WriteFile(EFilePathType::SOLUTION, tcScriptTxtPath, strStream);
#pragma endregion


	// strStream << TEXT("\n");
#pragma region Script Manager Header
	strStream.clear();
	
	strStream << TEXT("#pragma once\n");
	strStream << TEXT("#include \"pch.h\" \n");
	strStream << TEXT("#include <RokaSTL/SingleTon.h>\n");
	strStream << TEXT("class CScript;\n");
	strStream << TEXT("#ifdef SCRIPTDLL_EXPORTS \n");
	strStream << TEXT("#define SCRIPTDLL_DECLSPEC __declspec(dllexport) \n");
	strStream << TEXT("#else \n");
	strStream << TEXT("#define SCRIPTDLL_DECLSPEC __declspec(dllimport)\n");
	strStream << TEXT("#endif // CREATEDLL_EXPORTS\n");
	strStream << TEXT("enum class SCRIPTDLL_DECLSPEC EScriptType\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		NONE,\n");

	for (int i = 0; i < ScriptTypeCnt; ++i)
	{
		strStream << TEXT("		") << vecScriptFileNameList[i] << TEXT(",\n");
	}
	strStream << TEXT("		END,\n");
	strStream << TEXT("};\n");

	strStream << TEXT("class SCRIPTDLL_DECLSPEC ScriptManager:public rokaStl::IScriptManager,public rokaStl::Singleton<ScriptManager>\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		SINGLETON(ScriptManager)\n");
	strStream << TEXT("		MANAGER\n");
	strStream << TEXT("private:\n");
	strStream << TEXT("public:\n");
	strStream << TEXT("		virtual void GetScriptsInfo(std::vector<const TCHAR*>& _vec)override;\n");
	strStream << TEXT("		virtual CScript* GetScript(unsigned int _ScriptType)override;\n");
	strStream << TEXT("		virtual CScript* GetScript(const TCHAR* _ScriptName)override;\n");
	strStream << TEXT("		virtual const wchar_t* GetScriptName(CScript* _pScript)override;\n");
	strStream << TEXT("};\n");
	strStream << TEXT("extern \"C\"\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		SCRIPTDLL_DECLSPEC void ScriptManagerCreate();\n");
	strStream << TEXT("		SCRIPTDLL_DECLSPEC void ScriptManagerDestory();\n");
	strStream << TEXT("		SCRIPTDLL_DECLSPEC ScriptManager* GetScriptManager();\n");
	strStream << TEXT("}\n");

	M_FILE->WriteFile(EFilePathType::PROJECT, TEXT("\\Script\\ScriptManager.h"), strStream);
#pragma endregion 
	// strStream << TEXT("\n");
#pragma region Script Manager Cpp
	strStream.clear();
	strStream << TEXT("#include \"pch.h\"\n");
	strStream << TEXT("#include \"ScriptManager.h\"\n");
	for (int i = 0; i < ScriptTypeCnt; ++i)
	{
		strStream << TEXT("#include \"") << vecScriptFileNameList[i] << TEXT(".h\"\n");
	}
	strStream << TEXT("ScriptManager::ScriptManager()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("}\n");
	strStream << TEXT("ScriptManager::~ScriptManager()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("}\n");
	strStream << TEXT("void  ScriptManager::Initialize()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("}\n");
	strStream << TEXT("void ScriptManager::Loop()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("}\n");
	strStream << TEXT("void ScriptManager::Release()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("}\n");
	strStream << TEXT("void ScriptManager::GetScriptsInfo(std::vector<const TCHAR*>& _vec)\n");
	strStream << TEXT("{\n");
	for (int i = 0; i < ScriptTypeCnt; ++i)
	{
		strStream << TEXT("		_vec.push_back(TEXT(\"") << vecScriptFileNameList[i] << TEXT("\"));\n");
	}
	strStream << TEXT("}\n");
	strStream << TEXT("CScript* ScriptManager::GetScript(unsigned int _ScriptType)\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		EScriptType eType = (EScriptType)_ScriptType;\n");
	strStream << TEXT("		switch(eType)\n");
	strStream << TEXT("		{\n");
	for (int i = 0; i < ScriptTypeCnt; ++i)
	{
		strStream << TEXT("		case EScriptType::") << vecScriptFileNameList[i] << TEXT(":\n");
		strStream << TEXT("			return new ")<<vecScriptFileNameList[i]<<TEXT("(TYPETOINT(EScriptType::") << vecScriptFileNameList[i] << TEXT("));\n");
		strStream << TEXT("			break;\n");
	}
	strStream << TEXT("		}\n");
	strStream << TEXT("		return nullptr;\n");
	strStream << TEXT("}\n");

	strStream << TEXT("CScript* ScriptManager::GetScript(const TCHAR* _ScriptName)\n");
	strStream << TEXT("{\n");
	for (int i = 0; i < ScriptTypeCnt; ++i)
	{
		strStream << TEXT("		if(_tcscmp(_ScriptName , TEXT(\"") << vecScriptFileNameList[i] <<TEXT("\")) == 0)\n");
		strStream << TEXT("			return new ") << vecScriptFileNameList[i] << TEXT("(TYPETOINT(EScriptType::") << vecScriptFileNameList[i] << TEXT("));\n");
	}

	strStream << TEXT("		return nullptr;\n");
	strStream << TEXT("}\n");

	strStream << TEXT("const wchar_t* ScriptManager::GetScriptName(CScript* _pScript)\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		EScriptType eType =  (EScriptType)_pScript->GetScriptType();\n");
	strStream << TEXT("		switch (eType)\n");
	strStream << TEXT("		{\n");
	for (int i = 0; i < ScriptTypeCnt; ++i)
	{
		strStream << TEXT("		case EScriptType::") << vecScriptFileNameList[i] << TEXT(":\n");
		strStream << TEXT("			return TEXT(\"") << vecScriptFileNameList[i] << TEXT("\");\n");
		strStream << TEXT("			break;\n");
	}
	strStream << TEXT("		}\n");
	strStream << TEXT("		return nullptr;\n");
	strStream << TEXT("}\n");


	strStream << TEXT("SCRIPTDLL_DECLSPEC void ScriptManagerCreate()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		return MCreate(ScriptManager);\n");
	strStream << TEXT("}\n");
	strStream << TEXT("SCRIPTDLL_DECLSPEC void ScriptManagerDestory()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		return MDestroy(ScriptManager);\n");
	strStream << TEXT("}\n");
	strStream << TEXT("SCRIPTDLL_DECLSPEC ScriptManager* GetScriptManager()\n");
	strStream << TEXT("{\n");
	strStream << TEXT("		 return GetInst(ScriptManager);\n");
	strStream << TEXT("}\n");


	M_FILE->WriteFile(EFilePathType::PROJECT, TEXT("\\Script\\ScriptManager.cpp"), strStream);
#pragma endregion
	


	//excludelist 이외의 파일 목록 읽기.
	//scriptlist.txt 목록 읽기
	//폴더에서 script 목록 읽기
	//폴더 목록과 .txt 목록이 
	//  = 같은 경우 종료.
	//  = 다른 경우 (1) scriptlist.txt 내용 갱신 (2) 코드 쓰기


	M_FILE->FreeFileDetail(ExcludeList);
	M_FILE->FreeFileDetail(FileNameList);
	M_FILE->FreeFileDetail(SaveScriptTxtList);

	RKFileManager::Destroy();
}

