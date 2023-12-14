#include "pch.h"
#include <RokaSTL/MemoryPool.h>
#include "define.h"


class AClass : public rokaStl::MemoryPool
{
public:
	int a;
};

class BClass : public rokaStl::MemoryPool
{
private:
	int a;
	int b;
	int c;
	int d;
	int e;
};


int main()
{
	
	MemoryLeakCheck
	/*주의사항*/
	//////////////////////////
	// 1.MemoryPool을 꼭 1번 Initialize()해줘야 한다.
	//	이유는 내가 만든 map을 사용중인데, map test code를 보면 
	//	innerDelete라는 부분이 있다.
	//	내부에서 내가 넣은 데이터를 정리해주길 바랄때 쓰는 옵션으로 내가 구현한 MemoryPool에서는 필수이다.
	// 2.Memory Pool n Byte구역을 다 쓰고 다음 구역을 생성하는 코드를 보고 싶다면 .h MEMORY_BYTE 수치를 조정하여 테스트 한다. 
	//   이때 단위는 8byte*2*n 단위이다.
	//////////////////////////

    //Memorypool TestCode
    //////////////////////////
	// MEMORY_BYTE 64 기준.
	// [0] memorypool 내부 map에서 알아서 데이터 정리하도록 옵션 설정.
	// [1] new operator memorypool 구역 할당 or 생성.
	// [2] 8*2*n byte의 구역을 추가로 할당받아 사용하기.
	// [3] memory pool에 반납과 재사용.
	//////////////////////////
	//[0]
	rokaStl::MemoryPool::Initialize();
	//[1] 
	//BClass = 20 byte 이므로 32구역을 할당받음.
	AClass* data = new AClass();
	BClass* data2 = new BClass();//1구역의 1

	//[2] - 32byte pool 구역이 아래 첫번째 호출때 모두 사용.(1구역)
	//		두번째 호출때 32byte pool 구역을 추가 생성함.(2구역)
	//|--------------------| |--------------------|
	//|  32byte |  32byte  | |  32byte |  32byte  |
	//|--------------------| |--------------------|
	//       <1구역>                 <2구역>

	BClass* data3 = new BClass();//1구역의 2
	BClass* data4 = new BClass();//2구역의 1

	//[3] 
	delete data2;//1구역의 1 반납
	BClass* data5 = new BClass();//1구역의 1 재사용.
	BClass* data6 = new BClass();//2구역의 2.
    
	delete data4; // 2구역 1 반납
	delete data3; // 1구역 2 반납

	BClass* data7 = new BClass(); // 1구역 2 재사용.
	BClass* data8 = new BClass(); // 2구역 1 재사용.
								 
    //현재 모든 구역의 메모리들이 사용중이므로 
	//여기서 추가로 BClass* 를 또 할당받으면 2구역까지 모두 사용중이므로 3구역을 생성함.
	BClass* data9 = new BClass();

	//간단히 테스트 하기 위해 구역당 2개의 블럭이 잡히도록 한것이지만 MEMORYPOOL_BYTE 수치를 변경하면 됨.
	//현재 64 기준으로 했을때 32byte가 딱 2개로 맞아떨어지게 잡은것이고,
	//AClass 의 경우 8byte로 아래와 같이 메모리가 잡힐 것임.
	//|-------------------------------| 
	//| 8 | 8 | 8 | 8 | 8 | 8 | 8 | 8 |     8byte 구역(64byte) = 8 메모리.
	//|-------------------------------| 
	//		       <1구역>
}	        