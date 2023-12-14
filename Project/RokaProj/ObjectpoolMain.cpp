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
	// [1] singleton �� �����ֱ⸦ ��Ȯ�ϰ� �ϱ� ���� Create , Destroy �� ����� �Ѵ�.
	// [2] pool�� init�� ȣ������� �Ѵ�. 
	//	  (�� pool���� �ڽ��� �ʿ��� type�� ������Ʈ���� AddPool ����� �Ѵ�.)
	// [3] pool handle�� GetPool�� �Ͽ��� pool manager�� �����ϴ� pool�� ���ͼ� ��ü�� spawn �Ѵ�. 
	// [4] despawn
	//     ��ü���� smart pointer�� �޾ƿ��� ������ ���� pointer�� 0���� ������ despawn�� ȣ��ȴ�.
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