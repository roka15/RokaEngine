#pragma once
#include "Entity.h"

class CTransform;

#define GET_COMPONENT(type,Etype) C##type* type()const {return nullptr;}
class CGameObject :
    public CEntity
{
public:

public:
    GET_COMPONENT(Transform, TRANSFORM)
};

