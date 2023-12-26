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


	//excludelist �б�
	//excludelist �̿��� ���� ��� �б�.
	//scriptlist.txt ��� �б�
	//�������� script ��� �б�
	//���� ��ϰ� .txt ����� 
	//  = ���� ��� ����.
	//  = �ٸ� ��� �ڵ� ����.

	RKFileManager::Destroy();
}

