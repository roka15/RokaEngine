#pragma once
#include<iostream>
template<typename T>
class RKSTL
{
public:
	void Print(T* data);
};


template<>
inline void RKSTL<char>::Print(char* data)
{
	std::cout << data << std::endl;
}

template<typename T>
inline void RKSTL<T>::Print(T* data)
{
	std::cout << *data << std::endl;
}
