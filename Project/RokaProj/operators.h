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
struct PCharGreater
{
	bool operator()(const char* data1, const char* data2)
	{
		return *data1 < *data2;
	}
};
struct PCharLess
{
	bool operator()(const char* data1, const char* data2)
	{
		return *data1 > *data2;
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
