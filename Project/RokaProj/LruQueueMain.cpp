#include "pch.h"
#include <RokaSTL/LRU_Queue.h>
#include "define.h"

class AClass
{
public:
	AClass():mTime(-1.0f),mName(nullptr) {}
	AClass(double time,const char* name) :mTime(time),mName(name) {}
	AClass(const AClass& ref):mTime(ref.mTime),mName(ref.mName){}
	const double& GetTime()const { return mTime; }
	const char* GetName()const { return mName; }
	bool operator==(const AClass& other)
	{
		return (this->mTime == other.mTime) && (strcmp(this->mName, other.mName) == 0);
	}
private:
	double mTime;
	const char* mName;
};

struct AClassGreater
{
	bool operator()(const AClass& data1, const AClass& data2)
	{
		return data1.GetTime() < data2.GetTime();
	}
};
struct AClassLess
{
	bool operator()(const AClass& data1, const AClass& data2)
	{
		return data1.GetTime() > data2.GetTime();
	}
};
int main()
{
	//Default Test
	//////////////////////////////////////////////////////////////
	// [0] init capacity 설정
	// [1] push
	// [2] outdata (우선순위 낮은것을 빼고 새로운 데이터 추가 및 정렬
	// [3] while-empty-front-pop
	//////////////////////////////////////////////////////////////
	//[0]
	rokaStl::LRU_Queue<int, IntLess> intLru(5);
	int outdata = 0;
	//[1]
	intLru.Push(3, outdata);
	intLru.Push(5, outdata);
	intLru.Push(1, outdata);
	intLru.Push(2, outdata);
	intLru.Push(4, outdata);

	//[2]
	intLru.Push(0, outdata);
	intLru.Push(1, outdata);

	//[3]
	while (intLru.Empty() == false)
	{
		std::cout<<intLru.Front()<<std::endl;
		intLru.Pop();
	}

	//Pair Test
	rokaStl::LRU_Queue<std::pair<double, char>, TimePairGreater<char>> pairLru(5);
	std::pair<double, char> outdata2 = {};
	//[1]
	pairLru.Push(std::make_pair(0.5, 'C'), outdata2);
	pairLru.Push(std::make_pair(0.1, 'B'), outdata2);
	pairLru.Push(std::make_pair(0.7, 'D'), outdata2);
	pairLru.Push(std::make_pair(1.0, 'E'), outdata2);
	pairLru.Push(std::make_pair(1.1, 'F'), outdata2);

	//[2]
	pairLru.Push(std::make_pair(0.0, 'A'), outdata2);
    
	//[3]
	while (pairLru.Empty() == false)
	{
		std::cout << pairLru.Front().second << std::endl;
		pairLru.Pop();
	}

	//class Test
	//[0]
	rokaStl::LRU_Queue<AClass, AClassLess> classLru(5);
	AClass outdata3(0,"nullptr");
	//[1]
	classLru.Push(AClass(1,"A"), outdata3);
	classLru.Push(AClass(5,"E"), outdata3);
	classLru.Push(AClass(3,"C"), outdata3);
	classLru.Push(AClass(4,"D"), outdata3);
	classLru.Push(AClass(2,"B"), outdata3);

	//[2]
	classLru.Push(AClass(0,"AA"), outdata3);

	//[3]
	while (classLru.Empty() == false)
	{
		std::cout << classLru.Front().GetName() << std::endl;
		classLru.Pop();
	}

}