#pragma once

char* str2pchar(std::string& str);
void AssignmentTCHAR(TCHAR* _origin, const TCHAR* _change);
std::shared_ptr<TCHAR> AddTCHAR(const TCHAR* _origin, const TCHAR* _addstr);
std::shared_ptr<wchar_t> ConvertC2WC(char* _str);
std::shared_ptr<char> ConvertWC2C(wchar_t* _str);