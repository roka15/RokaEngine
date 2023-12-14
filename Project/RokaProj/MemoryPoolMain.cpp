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
	/*���ǻ���*/
	//////////////////////////
	// 1.MemoryPool�� �� 1�� Initialize()����� �Ѵ�.
	//	������ ���� ���� map�� ������ε�, map test code�� ���� 
	//	innerDelete��� �κ��� �ִ�.
	//	���ο��� ���� ���� �����͸� �������ֱ� �ٶ��� ���� �ɼ����� ���� ������ MemoryPool������ �ʼ��̴�.
	// 2.Memory Pool n Byte������ �� ���� ���� ������ �����ϴ� �ڵ带 ���� �ʹٸ� .h MEMORY_BYTE ��ġ�� �����Ͽ� �׽�Ʈ �Ѵ�. 
	//   �̶� ������ 8byte*2*n �����̴�.
	//////////////////////////

    //Memorypool TestCode
    //////////////////////////
	// MEMORY_BYTE 64 ����.
	// [0] memorypool ���� map���� �˾Ƽ� ������ �����ϵ��� �ɼ� ����.
	// [1] new operator memorypool ���� �Ҵ� or ����.
	// [2] 8*2*n byte�� ������ �߰��� �Ҵ�޾� ����ϱ�.
	// [3] memory pool�� �ݳ��� ����.
	//////////////////////////
	//[0]
	rokaStl::MemoryPool::Initialize();
	//[1] 
	//BClass = 20 byte �̹Ƿ� 32������ �Ҵ����.
	AClass* data = new AClass();
	BClass* data2 = new BClass();//1������ 1

	//[2] - 32byte pool ������ �Ʒ� ù��° ȣ�⶧ ��� ���.(1����)
	//		�ι�° ȣ�⶧ 32byte pool ������ �߰� ������.(2����)
	//|--------------------| |--------------------|
	//|  32byte |  32byte  | |  32byte |  32byte  |
	//|--------------------| |--------------------|
	//       <1����>                 <2����>

	BClass* data3 = new BClass();//1������ 2
	BClass* data4 = new BClass();//2������ 1

	//[3] 
	delete data2;//1������ 1 �ݳ�
	BClass* data5 = new BClass();//1������ 1 ����.
	BClass* data6 = new BClass();//2������ 2.
    
	delete data4; // 2���� 1 �ݳ�
	delete data3; // 1���� 2 �ݳ�

	BClass* data7 = new BClass(); // 1���� 2 ����.
	BClass* data8 = new BClass(); // 2���� 1 ����.
								 
    //���� ��� ������ �޸𸮵��� ������̹Ƿ� 
	//���⼭ �߰��� BClass* �� �� �Ҵ������ 2�������� ��� ������̹Ƿ� 3������ ������.
	BClass* data9 = new BClass();

	//������ �׽�Ʈ �ϱ� ���� ������ 2���� ���� �������� �Ѱ������� MEMORYPOOL_BYTE ��ġ�� �����ϸ� ��.
	//���� 64 �������� ������ 32byte�� �� 2���� �¾ƶ������� �������̰�,
	//AClass �� ��� 8byte�� �Ʒ��� ���� �޸𸮰� ���� ����.
	//|-------------------------------| 
	//| 8 | 8 | 8 | 8 | 8 | 8 | 8 | 8 |     8byte ����(64byte) = 8 �޸�.
	//|-------------------------------| 
	//		       <1����>
}	        