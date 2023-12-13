#pragma once
#include "CommonInclude.h"
namespace rokaStl
{
#define MEMORY_BYTE 32768 //32KB
	template <typename Key, typename Value>
	class RBT;

	typedef char* PBYTE;
	class MemoryPool
	{
	public:
		enum class EMemErrType
		{
			WRONGSIZE = -1,//���� �Է�
			POOLSIZEOVER = 0,// (32KB/2) ���� ū ������ �Ҵ��.
		};
		struct memory_pool_info
		{
			memory_pool_info();
			memory_pool_info(std::size_t capacity, std::size_t _size);
			~memory_pool_info();
			bool AddMemoryPool(std::size_t _capacity, std::size_t _size);

			PBYTE current;
			std::vector<PBYTE> memorys;
		};

		static void Test() {}
		static void Initialize();
		static void Release();

		static void* operator new(std::size_t _size);

		static void operator delete(void* _memory, std::size_t _size);
		static int AssignSize(std::size_t _size);
	public:

		using memorypool_t = RBT<size_t, MemoryPool::memory_pool_info*>;
	private:
		static memorypool_t m_memory_pools;
		static std::shared_ptr<memorypool_t> sp_pools;
	};

}

