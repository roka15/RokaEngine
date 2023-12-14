#include "pch.h"
#include "RBT.h"
#include "MemoryPool.h"

namespace rokaStl
{
	MemoryPool::memorypool_t MemoryPool::m_memory_pools;
    std::shared_ptr<MemoryPool::memorypool_t> MemoryPool::sp_pools(&m_memory_pools
	, [](void*)->void {std::cout << "release" << std::endl; MemoryPool::Release(); });

MemoryPool::memory_pool_info::memory_pool_info() :current(nullptr)
{
}

MemoryPool::memory_pool_info::memory_pool_info(std::size_t _capacity, std::size_t _size) : current(nullptr)
{
	AddMemoryPool(_capacity, _size);
}
bool MemoryPool::memory_pool_info::AddMemoryPool(std::size_t _capacity, std::size_t _size)
{
	current = (PBYTE)malloc(_capacity);

	if (current == nullptr)
	{
		//err �߻� ��Ű��.
		return false;
	}

	memset(current, 0, _capacity);
	int cnt = _capacity / _size;
	//32KB ���� �Ѱ� �̻��϶� ���� ���� ������ �ּҿ� ���� ���� ���� �� �ּҸ� ����.
	if (memorys.size() != 0)
	{
		PBYTE befor_mem = memorys[memorys.size() - 1];
		befor_mem += (_size * (cnt - 1));
		if (*befor_mem == '\0')
		{
			memcpy(befor_mem, &current, sizeof(PBYTE));
		}
	}

	PBYTE curptr = current;
	PBYTE nextptr = nullptr;
	for (int i = 0; i < cnt - 1; i++)
	{
		nextptr = curptr + _size;
		memcpy(curptr, &nextptr, sizeof(PBYTE));
		curptr = nextptr;
	}
	*curptr = '\0'; // �޸� ������ ����.

	memorys.push_back(current);
	return true;
}
MemoryPool::memory_pool_info::~memory_pool_info()
{
	for (int i=0;i<memorys.size();i++) 
	{
		delete memorys[i];
		memorys[i] = nullptr;
	}
	current = nullptr;
	memorys.clear();
	memorys.~vector();
}

void MemoryPool::Initialize()
{
	m_memory_pools.innerClear();
}

void MemoryPool::Release()
{
	//for (auto pool_info = m_memory_pools.begin();pool_info!=m_memory_pools.end();pool_info++)
	//{
	//	delete (*pool_info);
	//	(*pool_info) = nullptr;
	//}
	/* �ϰ� �;����� for(auto pool_info : m_memory_pools) */
	m_memory_pools.clear();
}

void* MemoryPool::operator new(std::size_t _size)
{
	int size = AssignSize(_size);
	if (size == (int)EMemErrType::POOLSIZEOVER)
	{
		return malloc(_size); // ���� �޸� �Ҵ�.
	}
	else if (size == (int)EMemErrType::WRONGSIZE)
	{
		return nullptr;
	}
	
	if (m_memory_pools.find(size) == m_memory_pools.end())
	{
		m_memory_pools.insert(std::make_pair(size, new memory_pool_info(MEMORY_BYTE, size)));
	}
	else if (m_memory_pools[size]->current == nullptr)
	{
		m_memory_pools[size]->AddMemoryPool(MEMORY_BYTE, size);
	}
	//success code
	PBYTE return_ptr = m_memory_pools[size]->current;
	PBYTE next_ptr = *reinterpret_cast<PBYTE*>(return_ptr);
	//fail code 
	//�ھƼ��� ��ũ :https://ramingstudy.tistory.com/73
	/*
	BYTE* next_ptr = reinterpret_cast<BYTE*>(*(m_memory_pools[size].current));
	BYTE* return_ptr = m_memory_pools[size].current;
	*/
	m_memory_pools[size]->current = next_ptr;

	return return_ptr;
}

void MemoryPool::operator delete(void* _memory, std::size_t _size)
{
	int size = AssignSize(_size);
	if (size == (int)EMemErrType::POOLSIZEOVER)
	{
		free(_memory); // ���� �޸� �Ҵ�.
		return;
	}
	else if (size == (int)EMemErrType::WRONGSIZE)
	{
		return;
	}


	PBYTE next_ptr = m_memory_pools[size]->current;
	memcpy(_memory, &m_memory_pools[size]->current, sizeof(PBYTE));
	m_memory_pools[size]->current = reinterpret_cast<PBYTE>(_memory);
}

int MemoryPool::AssignSize(std::size_t _size)
{
	if (_size * 2 > MEMORY_BYTE)
	{
		return static_cast<int>(EMemErrType::POOLSIZEOVER);
	}
	int befor = 0;
	for (int i = 8; ; i *= 2)
	{
		if (i > MEMORY_BYTE / 2)
			break;
		if (_size > befor && _size <= i)
		{
			return i;
		}
		befor = i;
	}

	return static_cast<int>(EMemErrType::WRONGSIZE);
}

}