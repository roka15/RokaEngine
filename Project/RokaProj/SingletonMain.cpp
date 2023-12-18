#include "pch.h"
#include <RokaSTL/SingleTon.h>
#include <RokaSTL/define.h>
#include "operators.h"

class TestA : public rokaStl::Singleton<TestA>
{
	SINGLETON(TestA)
public:
	int a;
};

TestA::TestA()
{

}
TestA::~TestA()
{

}

int main()
{
	MemoryLeakCheck
	//Singleton Test
	TestA::Create();
	TestA* instance = GetInstance(TestA);
	TestA* instance2 = GetInstance(TestA);
	TestA::Destroy();
}