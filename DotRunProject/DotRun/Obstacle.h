#pragma once

#include "CollisionObject.h"

class Obstacle : public CollisionObject
{
public:
	Obstacle(int);
	~Obstacle();
	void CollisionEvent(GameManager* gameManager);
};

