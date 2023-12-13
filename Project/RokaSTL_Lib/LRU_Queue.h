#pragma once

#include "PriorityQueue.h"
namespace rokaStl
{
	template<typename T, typename _Pr = greater<T>>
	class LRU_Queue
	{
	private:
		typedef PriorityQueue<T, _Pr> priority_queue;
	public:
		LRU_Queue(int _capacity) :capacity(_capacity) { queue = new priority_queue(_capacity); }
		~LRU_Queue() { delete queue; }
		bool Push(T _data, T& outdata)
		{
			bool flag = false;
			if (queue->Size() == capacity)
			{
				outdata = queue->Front();
				queue->Pop();
				flag = true;
			}
			queue->Push(_data);
			return flag;
		}
		bool Empty()
		{
			return queue->Empty();
		}
		T Front()
		{
			return queue->Front();
		}
		void Pop()
		{
			queue->Pop();
		}
		int Size()
		{
			return queue->Size();
		}
		void Sort()
		{
			queue->Sort();
		}
		void Capacity(size_t _capacity)
		{
			if (capacity > _capacity)
			{
				size_t diff = capacity > queue->Size() ? queue->Size() : capacity;
				CustomDelete<T>(diff - _capacity);
			}
			capacity = _capacity;
		}
		/*�����̳��� ���� �����°��̱� ������ ���� X,���� X ����� ���� ��¸� �Ѵ�.
		  lru���� �����ϴ� render���� Ÿ�Ͽ� ���� ������ ��� ���ؼ� �������.*/
		const T& operator[](int _index)
		{
			return (*queue)[_index];
		}
	protected:
		template<typename U = T, typename = std::enable_if_t<std::is_same_v<U, std::shared_ptr<typename T::element_type>>>>
		void CustomDelete(size_t _delete_cnt)
		{
			for (int i = 0; i < _delete_cnt; i++)
			{
				T data = queue->Front();
				queue->Pop();
				data.reset();
			}
		}
		template<typename U = T, typename std::enable_if_t<std::is_pointer_v<U>>* = nullptr>
		void CustomDelete(size_t _delete_cnt)
		{
			for (int i = 0; i < _delete_cnt; i++)
			{
				T data = queue->Front();
				queue->Pop();

				delete data;
			}
		}
	protected:
		class priority_queue* queue;
	private:
		int capacity;
	};
}