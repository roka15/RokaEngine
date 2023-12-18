#pragma once
#include "interface.h"
#include <RokaSTL/SingleTon.h>
#include <RokaSTL/define.h>


class GenericManager : public IManager,public rokaStl::Singleton<GenericManager>
{
	SINGLETON(GenericManager)
public:
	virtual void Initialize()override;
	virtual void Release()override;
private:

};




