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
	TestA* instance = GetInst(TestA);
	TestA* instance2 = GetInst(TestA);
	TestA::Destroy();
}