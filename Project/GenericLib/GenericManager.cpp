#include "pch.h"
#include "GenericManager.h"

GenericManager* GenericManager::minstance = nullptr;
GenericManager::GenericManager()
{

}
GenericManager::~GenericManager()
{

}
GenericManager* GenericManager::GetInst()
{
	if (minstance == nullptr)
		minstance = new GenericManager();

	return minstance;
}

void GenericManager::Print()
{
	printf("%s", "Hello");
}


void GenericManager::Destroy()
{
	delete minstance;
}
