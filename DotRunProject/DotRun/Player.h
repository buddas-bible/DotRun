#pragma once

#include "CollisionObject.h"

class Player : public CollisionObject
{
public:
	Player();
	~Player();
	void CollisionEvent(GameManager* gameManager);
};