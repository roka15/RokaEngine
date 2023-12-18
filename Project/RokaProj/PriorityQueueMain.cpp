#include "pch.h"
#include <RokaSTL/PriorityQueue.h>
#include <RokaSTL/define.h>
#include "operators.h"

int main()
{
	//Priority Queue Test

	//Default Test(int)
	///////////////////////
	//  1.push
	//  2.size-for-pop
	//  3.empty-while-pop
	///////////////////////
	rokaStl::PriorityQueue<int, IntLess> number;
	number.Push(5);
	number.Push(2);
	number.Push(4);
	number.Push(1);
	number.Push(3);
	
	size_t size = number.Size();
	for (int i = 0; i < size; i++)
	{
		std::cout << number.Front() << std::endl;
		number.Pop();
	}

	number.Push(5);
	number.Push(2);
	number.Push(4);
	number.Push(1);
	number.Push(3);

	while (number.Empty() == false)
	{
		std::cout << number.Front() << std::endl;
		number.Pop();
	}

	//char
	rokaStl::PriorityQueue<char, CharLess> chars;
	chars.Push('e');
	chars.Push('a');
	chars.Push('c');
	chars.Push('d');
	chars.Push('b');

	size = chars.Size();
	for (int i = 0; i < size; i++)
	{
		std::cout << chars.Front() << std::endl;
		chars.Pop();
	}

	//char*
	char* c = new char[2];
	rokaStl::PriorityQueue<const char*, PCharLess> pchars;
	pchars.Push("e\0");
	pchars.Push("a\0");
	pchars.Push("c\0");
	pchars.Push("d\0");
	pchars.Push("b\0");


	while (pchars.Empty() == false)
	{
		std::cout << pchars.Front() << std::endl;
		pchars.Pop();
	}

}