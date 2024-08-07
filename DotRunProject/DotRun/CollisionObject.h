#pragma once

#include "PixelObject.h"

class GameManager;

class CollisionObject : public PixelObject
{
public:
	CollisionObject();
	~CollisionObject();
	void CollisionEvent(GameManager* gameManager);
};