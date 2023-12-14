#include "pch.h"
#include <RokaSTL/SingleTon.h>
#include "define.h"
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
	TestA* instance = TestA::GetInstance();
	TestA* instance2 = TestA::GetInstance();
	TestA::Destroy();
}