#include "pch.h"
#include "func.h"

char* str2pchar(std::string& str)
{
size_t len = str.size();
char* temp = new char[len+1];
memset(temp, '\0', len + 1);
str.copy(temp, len);

return temp;
}

void AssignmentTCHAR(TCHAR* _origin, const TCHAR* _change)
{
	size_t len = _tcslen(_origin);
	memset(_origin, 0, len);

	_tcscpy(_origin, _change);
}

std::shared_ptr<TCHAR> AddTCHAR(const TCHAR* _origin, const TCHAR* _addstr)
{
	std::shared_ptr<TCHAR> result(new TCHAR[MAX_PATH]);
	ZeroMemory(result.get(), MAX_PATH);

	AssignmentTCHAR(result.get(), _origin);
	_tcscat(result.get(), _addstr);
	return result;
}
std::shared_ptr<wchar_t> ConvertC2WC(char* _str)
{
	int strSize = MultiByteToWideChar(CP_ACP, 0, _str, -1, NULL, NULL);
	std::shared_ptr<wchar_t> pStr(new wchar_t[strSize]);
	MultiByteToWideChar(CP_ACP, 0, _str, strlen(_str)+1, pStr.get(), strSize);
	return pStr;
}
std::shared_ptr<char> ConvertWC2C(wchar_t* _str)
{
	int strSize = WideCharToMultiByte(CP_ACP, 0, _str, -1, NULL, 0, NULL, NULL);
	std::shared_ptr<char> pStr(new char[strSize]);
	WideCharToMultiByte(CP_ACP, 0, _str, -1, pStr.get(), strSize, 0, 0); 
	return pStr;

}