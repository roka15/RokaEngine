#pragma once
#include "pch.h"
#include <RokaSTL/interface.h>
//#include <Roka>
#include <RokaSTL/SingleTon.h>
class CSaveLoadManager : public rokaStl::IManager,public rokaStl::Singleton<CSaveLoadManager>
{
	SINGLETON(CSaveLoadManager)
	MANAGER
private:
	//rokaStl::RBT<>
public:
	
};

