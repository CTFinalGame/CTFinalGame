#pragma once
#include "SweptAABB.h"
#include "../../Objects/BaseObject.h"

class Collision
{
	D3DXVECTOR2 velocity;

public:
	Collision();
	DIR isCollision(BaseObject*, BaseObject*);
	D3DXVECTOR2		getVelocity(){ return velocity; };
	~Collision();
};

