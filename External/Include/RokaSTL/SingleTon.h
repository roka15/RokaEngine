#pragma once
#include "CommonInclude.h"

namespace rokaStl
{
	typedef void (*EXIT_FUNC)(void);
	template <typename T>
	class Singleton
	{
	public:
		static void Create()
		{
			if (minstance == nullptr)
				minstance = new T();
		}
		static void Destroy()
		{
			if (minstance != nullptr)
			{
				delete	minstance;
				minstance = nullptr;
			}
		}
		static T*const& GetInstance()
		{
			return minstance;
		}
	private:
		static T* minstance;
	};

	template<typename T>
	T* Singleton<T>::minstance = nullptr;
}


