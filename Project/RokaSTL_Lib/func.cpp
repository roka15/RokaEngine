#include "pch.h"
#include "func.h"

char* str2pchar(std::string& str)
{
size_t len = str.size();
char* temp = new char[len];
memset(temp, '\0', len + 1);
str.copy(temp, len + 1);

return temp;
}