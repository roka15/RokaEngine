
#include "pch.h"

#include <iostream>
class A
{
public:
	virtual ~A() {}
};
class B : public A
{
public:
	virtual ~B() {}
};
int main()
{
	
	//GenericManager* ptr = GetMGenericInst();
    
	

	A* b = new B();
	decltype(b) a;
	//std::cout << typeid(*b).name << std::endl;


	
	return 0;
}