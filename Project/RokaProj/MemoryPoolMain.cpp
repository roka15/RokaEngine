#include <RokaSTL/MemoryPool.h>
#include "define.h"
class AClass : public rokaStl::MemoryPool
{
public:
	int a;
};
int main()
{
	MemoryLeakCheck
		rokaStl::MemoryPool::Test();
	//AClass* data = new AClass();

}