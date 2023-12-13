#include <RokaSTL/SingleTon.h>

class TestA : public rokaStl::Singleton<TestA>
{
public:
	int a;
};

int main()
{
	//Singleton Test
	TestA* instance = TestA::GetInstance();
	TestA* instance2 = TestA::GetInstance();

}