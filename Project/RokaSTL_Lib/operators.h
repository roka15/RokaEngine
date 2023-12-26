#pragma once
#include <iostream>

namespace rokaStl
{
	template<typename T>
	class Singleton;
}

struct IntGreater
{
	bool operator()(const int& data1, const int& data2)
	{
		return data1 < data2;
	}
};
struct IntLess
{
	bool operator()(const int& data1, const int& data2)
	{
		return data1 > data2;
	}
};

struct CharGreater
{
	bool operator()(const char& data1, const char& data2)
	{
		return data1 < data2;
	}
};
struct CharLess
{
	bool operator()(const char& data1, const char& data2)
	{
		return data1 > data2;
	}
};
struct PCharEqual
{
	bool operator()(const char* data1, const char* data2)
	{
		return strcmp(data1, data2) == 0;
	}
};
struct PTCharEqual
{
	bool operator()(const TCHAR* data1, const TCHAR* data2)
	{
		return _tcscmp(data1, data2) == 0;
	}
};
struct PCharGreater
{
	bool operator()(const char* data1, const char* data2)
	{
		size_t len1 = strlen(data1);
		size_t len2 = strlen(data2);
		if (len1 != len2)
		{
			if (len1 < len2)
				return true;
			else if (len1 > len2)
				return false;
		}


		size_t len = len1;
		for (int i = 0; i < len; ++i)
		{
			if (data1[i] == data2[i])
				continue;
			else
			{
				return data1[i] > data2[i];
			}
		}

		return false;
	}
};
struct PCharLess
{
	bool operator()(const char* data1, const char* data2)
	{
		size_t len1 = strlen(data1);
		size_t len2 = strlen(data2);
		if (len1 != len2)
		{
			if (len1 > len2)
				return true;
			else if (len1 < len2)
				return false;
		}

		size_t len = len1;
		for (int i = 0; i < len; ++i)
		{
			if (data1[i] == data2[i])
				continue;
			else
			{
				return data1[i] < data2[i];
			}
		}

		return false;
	}
};

struct PTCharGreater
{
	bool operator()(const TCHAR* data1, const TCHAR* data2)
	{
		size_t len1 = _tcslen(data1);
		size_t len2 = _tcslen(data2);
		if (len1 != len2)
		{
			if (len1 < len2)
				return true;
			else if (len1 > len2)
				return false;
		}


		size_t len = len1;
		for (int i = 0; i < len; ++i)
		{
			if (data1[i] == data2[i])
				continue;
			else
			{
				return data1[i] > data2[i];
			}
		}

		return false;
	}
};
struct PTCharLess
{
	bool operator()(const TCHAR* data1, const TCHAR* data2)
	{
		size_t len1 = _tcslen(data1);
		size_t len2 = _tcslen(data2);
		if (len1 != len2)
		{
			if (len1 > len2)
				return true;
			else if (len1 < len2)
				return false;
		}

		size_t len = len1;
		for (int i = 0; i < len; ++i)
		{
			if (data1[i] == data2[i])
				continue;
			else
			{
				return data1[i] < data2[i];
			}
		}

		return false;
	}
};
template<typename Y>
struct TimePairGreater
{
	bool operator()(std::pair<double, Y> data1, std::pair<double, Y> data2)
	{
		return data1.first < data2.first;
	}
};
template<typename Y>
struct TimePairLess
{
	bool operator()(std::pair<double, Y> data1, std::pair<double, Y> data2)
	{
		return data1.first > data2.first;
	}
};
