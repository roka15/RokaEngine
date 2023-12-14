#pragma once
#include "CommonInclude.h"
#include "interface.h"
#include "ObjectPool.h"
#include "SingleTon.h"

namespace rokaStl
{
	template <typename Pool,typename Origin>
	class ObjectPoolManager : public Singleton<Pool>,public IRkStlBase
	{
	public:
		ObjectPool<Origin>* GetPool(std::wstring key)
		{
			if (key.size() == 0)
				return nullptr;


			typename std::map<std::wstring, std::unique_ptr<ObjectPool<Origin>>>::iterator itr;
			itr = mPools.find(key);
			if (itr == mPools.end())
				return nullptr;
            
			return itr->second.get();
		}
		virtual std::shared_ptr<Origin> Spawn(std::wstring key)
		{
			ObjectPool<Origin>* pool = GetPool(key);
			std::shared_ptr<Origin> object = pool->Spawn();
			return object;
		}
	
	protected:
		virtual void Initialize() = 0;
		virtual void Release() = 0;
		

		ObjectPoolManager() { mPoolSize = 100; }
		virtual ~ObjectPoolManager() 
		{
			mPools.clear();
		}
	
		template <typename ObjType>
		bool AddPool(std::wstring key, std::shared_ptr<ObjType> origin, size_t pool_size)
		{
			if (mPools.find(key) != mPools.end())
				return false;
			ObjectPool<ObjType>* objType_pool = new ObjectPool<ObjType>();
			objType_pool->Initialize(origin, pool_size);
			ObjectPool<Origin>* originType_pool = reinterpret_cast<ObjectPool<Origin>*>(objType_pool);
			mPools.insert(std::make_pair(key, std::unique_ptr<ObjectPool<Origin>>(originType_pool)));
			return true;
		}
		template <typename ObjType>
		bool AddPool(std::wstring key, std::shared_ptr<ObjType> origin)
		{
			if (mPools.find(key) != mPools.end())
				return false;
			ObjectPool<ObjType>* objType_pool = new ObjectPool<ObjType>();
			objType_pool->Initialize(origin, mPoolSize);
			ObjectPool<Origin>* originType_pool = reinterpret_cast<ObjectPool<Origin>*>(objType_pool);
			mPools.insert(std::make_pair(key, std::unique_ptr<ObjectPool<Origin>>(originType_pool)));
			return true;
		}
	protected:
		size_t mPoolSize;
		std::map<std::wstring, std::unique_ptr<ObjectPool<Origin>>> mPools;
	};

}

