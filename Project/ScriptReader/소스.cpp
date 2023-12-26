#include <CommonInclude.h>

typedef typename rokaStl::FileManager RKFileManager;
#define M_FILE RKFileManager::GetInstance()

int main()
{
	RKFileManager::Create();
	const TCHAR* tcProjPath = M_FILE->GetProjectPath();
	TCHAR tcCppPath[MAXPATH]{};
	_tcscpy(tcCppPath, tcProjPath);
	_tcscat(tcCppPath, TEXT("\\Script\\ScriptManager.cpp"));

	TCHAR tcHeaderPath[MAXPATH]{};
	_tcscpy(tcHeaderPath, tcProjPath);
	_tcscat(tcHeaderPath, TEXT("\\Script\\ScriptManager.h"));


	//excludelist 읽기
	//excludelist 이외의 파일 목록 읽기.
	//scriptlist.txt 목록 읽기
	//폴더에서 script 목록 읽기
	//폴더 목록과 .txt 목록이 
	//  = 같은 경우 종료.
	//  = 다른 경우 코드 쓰기.

	RKFileManager::Destroy();
}

