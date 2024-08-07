#pragma once

#include "CollisionObject.h"

class Item : public CollisionObject
{
private:
	int itemType;
	int point;
	int power;
public:
	Item(int);
	~Item();
	void CollisionEvent(GameManager* gameManager);
};
