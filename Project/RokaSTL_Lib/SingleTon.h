#pragma once
#include "CommonInclude.h"

namespace rokaStl
{
	typedef void (*EXIT_FUNC)(void);
	template <typename T>
	class Singleton
	{
	public:
		static T* GetInstance()
		{
			if (minstance == nullptr)
			{
				minstance =new T();
				atexit((EXIT_FUNC)(&Singleton<T>::Destroy));
			}
			return minstance;
		}
		static void Destroy()
		{
			if (minstance != nullptr)
			{
				delete	minstance;
				minstance = nullptr;
			}
		}
	private:
		static T* minstance;
	};

	template<typename T>
	T* Singleton<T>::minstance = nullptr;
}


