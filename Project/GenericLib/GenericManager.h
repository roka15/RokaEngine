#pragma once
#include "interface.h"
#include <RokaSTL/SingleTon.h>
#include <RokaSTL/define.h>


class GenericManager : public IManager,public rokaStl::Singleton<GenericManager>
{
	SINGLETON(GenericManager)
	MANAGER
private:

};




