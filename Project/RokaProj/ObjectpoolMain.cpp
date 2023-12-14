#include <RokaSTL/ObjectPoolManager.h>
#include "define.h"
class GameObject
{
public:
	virtual ~GameObject() {}
	virtual void Print() {};
};
class Character : public GameObject
{
public:
	virtual ~Character() {};
	virtual void Print() {}
};
class Player : public Character
{
public:
	virtual ~Player() {};
	virtual void Print() {}
};
class Monster : public Character
{
public:
	virtual ~Monster() {};
	virtual void Print() {}
};
// player
class Mage : public Player
{
public:
	virtual ~Mage() {}
	virtual void Print()override
	{
		std::cout << "Mage" << std::endl;
	}
};
class Swordmaster : public Player
{
public:
	virtual ~Swordmaster() {}
	virtual void Print()override
	{
		std::cout << "Swordmaster" << std::endl;
	}
};

//monster
class Pig : public Monster
{
public:
	Pig() :a(10) {}
	int a;
	virtual ~Pig() {}
	virtual void Print()override
	{
		std::cout << "Pig" << std::endl;
	}
};
class Spider : public Monster
{
public:
	Spider() :b(5) {}
	int b;
	virtual ~Spider() {}
	virtual void Print()override
	{
		std::cout << "Spider" << std::endl;
	}
};
//origin prefab object
std::shared_ptr<Mage> mage = std::make_shared<Mage>();
std::shared_ptr<Swordmaster> sword = std::make_shared<Swordmaster>();

std::shared_ptr<Pig> pig = std::make_shared<Pig>();
std::shared_ptr<Spider> spider = std::make_shared<Spider>();


//pool
class PlayerPoolManager : public rokaStl::ObjectPoolManager<PlayerPoolManager, Player>
{
    SINGLETON(PlayerPoolManager)
public:
	virtual void Initialize()override 
	{
		mPoolSize = 100;
		bool success = AddPool<Mage>(L"Mage", mage,10);
		success = AddPool<Swordmaster>(L"SwordMaster", sword);
	};
	virtual void Release()override 
	{
	};
};
PlayerPoolManager::PlayerPoolManager() {}
PlayerPoolManager::~PlayerPoolManager() {}
class MonsterPoolManager : public rokaStl::ObjectPoolManager<MonsterPoolManager, Monster>
{
	SINGLETON(MonsterPoolManager)
public:
	virtual void Initialize()override
	{
		mPoolSize = 100;
		bool success = AddPool<Pig>(L"Pig", pig);
		success = AddPool<Spider>(L"Spider", spider);
	};
	virtual void Release()override 
	{
	};
};
MonsterPoolManager::MonsterPoolManager() {}
MonsterPoolManager::~MonsterPoolManager(){}
int main()
{
	MemoryLeakCheck

	//ObjectPoolManager & ObjectPool Test Code
	// //////////////////////////////////////////////////////////////////////////
	// [1] singleton 의 생성주기를 명확하게 하기 위해 Create , Destroy 를 해줘야 한다.
	// [2] pool의 init을 호출해줘야 한다. 
	//	  (각 pool들은 자신이 필요한 type의 오브젝트들을 AddPool 해줘야 한다.)
	// [3] pool handle로 GetPool을 하여서 pool manager가 관리하는 pool을 얻어와서 객체를 spawn 한다. 
	// [4] despawn
	//     객체들은 smart pointer로 받아오기 때문에 참조 pointer를 0으로 만들어야 despawn이 호출된다.
	// //////////////////////////////////////////////////////////////////////////
   
	//[1] create
	MonsterPoolManager::Create();
	PlayerPoolManager::Create();

	//[2] init
	MonsterPoolManager* instance1 = GetInstance(MonsterPoolManager)
	instance1->Initialize();
	//[3] spawn
	std::shared_ptr<Monster> monster1 = instance1->GetPool(L"Pig")->Spawn();
	std::shared_ptr<Monster> monster2 = instance1->GetPool(L"Spider")->Spawn();


	std::shared_ptr<Pig> temp = std::dynamic_pointer_cast<Pig>(monster1);
	temp->Print();
	monster2->Print();

	//[4] despawn
	monster1.reset();
	monster2.reset();
	temp.reset();


	PlayerPoolManager* instance2 = GetInstance(PlayerPoolManager)
	instance2->Initialize();
	instance2->GetPool(L"Mage")->Spawn()->Print();
	instance2->GetPool(L"SwordMaster")->Spawn()->Print();

	//[1] destroy
	MonsterPoolManager::Destroy();
	PlayerPoolManager::Destroy();
	return 0;
}