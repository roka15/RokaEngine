#pragma once

namespace General
{
	template <typename T>
	class SPtr
	{
	public:
		SPtr() :mRes(nullptr)
		{
		}
		SPtr(T* _res) :mRes(_res)
		{
			if (mRes != nullptr)
				mRes->AddRefCnt();
		}
		SPtr(const SPtr<T>& _ref) :mRes(_ref.get())
		{
			if (mRes != nullptr)
				mRes->AddRefCnt();
		}
		~SPtr()
		{
			if (mRes != nullptr)
				mRes->Release();
		}
	public:
		T* get()const
		{
			return mRes;
		}
		T* operator->()const
		{
			return mRes;
		}
		void operator=(T* _res)
		{
			if (mRes != nullptr)
				mRes->Release();
			mRes = _res;
			if (mRes != nullptr)
				mRes->AddRefCnt();
		}
		void operator=(SPtr<T> _res)
		{
			if (mRes != nullptr)
				mRes->Release();
			mRes = _res.get();
			if (mRes != nullptr)
				mRes->AddRefCnt();
		}
		bool operator==(T* _res)
		{
			return mRes == _res;
		}
		bool operator==(SPtr<T> _res)
		{
			return  mRes == _res.get();
		}
		bool operator!=(T* _res)
		{
			return mRes == _res;
		}
		bool operator!=(SPtr<T> _res)
		{
			return mRes == _res.get();
		}
	private:
		T* mRes;
	};

}