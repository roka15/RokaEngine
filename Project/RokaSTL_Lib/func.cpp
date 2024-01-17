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

void AssignmentTCHAR(TCHAR*& _origin, const TCHAR* _change)
{
	size_t len = _tcslen(_origin);
	memset(_origin, 0, len);

	_tcscpy(_origin, _change);
}