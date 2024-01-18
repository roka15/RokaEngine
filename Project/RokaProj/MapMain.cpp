#include "pch.h"
#include <RokaSTL/RBT.h>
#include <RokaSTL/define.h>

int main()
{   
	MemoryLeakCheck
	//map test
	// *주의사항*
	// 1. key값이 문자열인 경우 사전적으로 비교하기 때문에 사전적 정의가 높은쪽이 오른쪽 노드에 위치한다.
    // 2. 만약 innserClear 옵션 ON 라면 
	//    key 또는 value 에 const char*을 넣는 경우 동적할당을 한 경우로 통일한다. 
	//	  key = "Hello" (X) key = new char[100] (O)
	// 3. 만약 innserClear 옵션 OFF 라면 2번의 경우는 정 반대이다.
    //    key = "Hello" (O) key = new char[100] (X)
	
	//Default Test (Key = int)
	//////////////////////////////////////////////////////////////
	// [0] init 
	// [1] insert
    // [2] 중복 키는 추가 X.
	// [3] size
	// [4] iterator for
	// [5] find itr | operator[]
	// [6] erase -test 예제 통과 https://www.youtube.com/watch?v=6drLl777k-E
	// [7] memory leak 방지 release 처리.
	// [8] inner clear = map 내부에서 node 정리할때 value를 같이 정리해주길 바랄때 쓰는 옵션.
	// [9]  key* , value*
	// [10] key  , value*
	// [11] key* , value
	//////////////////////////////////////////////////////////////
	
	//[0]
	rokaStl::RBT<int, const char*> map1;
	//[1]
	map1.insert(std::make_pair(35, "35"));
	map1.insert(std::make_pair(20, "20"));
	map1.insert(std::make_pair(50, "50"));
	map1.insert(std::make_pair(10, "10"));
	map1.insert(std::make_pair(30, "30"));
	map1.insert(std::make_pair(40, "40"));
	map1.insert(std::make_pair(80, "80"));
	map1.insert(std::make_pair(5, "5"));
	map1.insert(std::make_pair(15, "15"));
	map1.insert(std::make_pair(25, "25"));
	map1.insert(std::make_pair(33, "33"));
	map1.insert(std::make_pair(37, "37"));
	map1.insert(std::make_pair(45, "45"));
	map1.insert(std::make_pair(2, "2"));
	map1.insert(std::make_pair(27, "27"));
	//[2]
	map1.insert(std::make_pair(40, "FF"));
	//[3]
	size_t size = map1.size();
	//[4]
	for (rokaStl::Iterator<int, const char*>::MapIterator itr = map1.begin(); itr != map1.end(); itr++)
	{
		std::cout << "Key:" << itr.GetKey() << " Data:" << itr.GetData() <<std::endl;
	}
	//[5]
	rokaStl::Iterator<int, const char*>::MapIterator itr1 = map1.find(2);
	const char* value1 = map1[2];
	//[6]
	map1.erase(15);
	map1.erase(33);
	map1.erase(37);
	map1.erase(35);
	map1.erase(40);
	map1.erase(50);
 	map1.erase(80);
	map1.erase(27);

	for (rokaStl::Iterator<int, const char*>::MapIterator itr = map1.begin(); itr != map1.end(); itr++)
	{
		std::cout << "Key:" << itr.GetKey() << " Data:" << itr.GetData() << std::endl;
	}
	//[7]
	map1.clear();

	//Value = int* Test
	rokaStl::RBT<int, int*> map2;
	//[8]
	map2.innerClear();

	map2.insert(std::make_pair(3, new int(3)));
	map2.insert(std::make_pair(1, new int(1)));
	map2.insert(std::make_pair(5, new int(5)));
	map2.insert(std::make_pair(2, new int(2)));
	map2.insert(std::make_pair(4, new int(4)));

	map2.insert(std::make_pair(4, new int(44)));
	for (rokaStl::Iterator<int,int*>::MapIterator itr = map2.begin(); itr != map2.end(); itr++)
	{
		std::cout << "Key:" << itr.GetKey() << " Data:" << *itr.GetData() << std::endl;
	}
	rokaStl::Iterator<int, int*>::MapIterator itr2 = map2.find(2);
	int* value2 = map2[2];
	map2.clear();

	
	//Key = const char* Test
	//사전식 비교.
	rokaStl::RBT<const char*,int,PCharEqual,PCharGreater,PCharLess> map3;
	map3.insert(std::make_pair("aa",1));
	map3.insert(std::make_pair("abc", 2));
	map3.insert(std::make_pair("ac",3));
	map3.insert(std::make_pair("ad",4));
	map3.insert(std::make_pair("ae",5));
	map3.insert(std::make_pair("abe",6));
	map3.insert(std::make_pair("ag", 7));
	map3.insert(std::make_pair("ahas", 7));
	map3.insert(std::make_pair("ai", 10));


	

	for (rokaStl::Iterator<const char*, int>::MapIterator itr = map3.begin(); itr != map3.end(); itr++)
	{
		std::cout << "Key:" << itr.GetKey() << " Data:" << itr.GetData() << std::endl;
	}
	rokaStl::Iterator<const char*, int>::MapIterator itr3 = map3.find("He");
	int value = map3["ai"];
	map3.clear();


	//[9]
	rokaStl::RBT<int*, char*> ptrTest1;
	ptrTest1.innerClear();
	ptrTest1.insert(std::make_pair(new int(1), new char[100]()));
	ptrTest1.clear();


	rokaStl::RBT<char*, int*> ptrTest2;
	ptrTest2.innerClear();
	ptrTest2.insert(std::make_pair(new char[100](), new int(1)));
	ptrTest2.clear();

	
	rokaStl::RBT<const char*, char*> ptrTest3;
	ptrTest3.innerClear();
	ptrTest3.insert(std::make_pair(new char[100](), new char[100]()));
	ptrTest3.clear();

	//[10]
	rokaStl::RBT<int, int*> ptrTest4;
	ptrTest4.innerClear();
	ptrTest4.insert(std::make_pair(1, new int(1)));
	ptrTest4.clear();

	rokaStl::RBT<int, char*> ptrTest5;
	ptrTest5.innerClear();
	ptrTest5.insert(std::make_pair(1, new char[100]()));
	ptrTest5.clear();

	rokaStl::RBT<int, const char*> ptrTest6;
	ptrTest6.innerClear();
	ptrTest6.insert(std::make_pair(1, new char[100]()));
	ptrTest6.clear();

	//[11]
	rokaStl::RBT<int*, int> ptrTest7;
	ptrTest7.innerClear();
	ptrTest7.insert(std::make_pair(new int(1), 1));
	ptrTest7.clear();

	rokaStl::RBT<char*, int> ptrTest8;
	ptrTest8.innerClear();
	ptrTest8.insert(std::make_pair(new char[100](), 1));
	ptrTest8.clear();

	rokaStl::RBT<const char*, int> ptrTest9;
	ptrTest9.innerClear();
	ptrTest9.insert(std::make_pair(new char[100](), 1));
	ptrTest9.clear();
}