#include "Item.h"
#include "DotRunDef.h"
#include "GameManager.h"

Item::Item(int type):
	itemType(type)
{
	if (type == ITEM_TYPE_POINTBOX)
	{
		init(true, 0, 0, 2, 1, LAYER_GAMEOBJECT);

		point = 10;
		power = 0;

		Chars = {
		{ ' ', ' ' },
		};

		Colors = {
			{ POINTBOX_COLOR, POINTBOX_COLOR },
		};
	}
	else if (type == ITEM_TYPE_POWERBOX)
	{
		init(true, 0, 0, 2, 1, LAYER_GAMEOBJECT);

		point = 10;
		power = 10;

		Chars = {
		{ ' ', ' ' },
		};

		Colors = {
			{ POWERBOX_COLOR, POWERBOX_COLOR },
		};
	}
	else if (type == ITEM_TYPE_SHIELD)
	{
		init(true, 0, 0, 2, 1, LAYER_GAMEOBJECT);

		point = 10;
		power = 0;

		Chars = {
		{ ' ', ' ' },
		};

		Colors = {
			{ SHIELD_COLOR, SHIELD_COLOR },
		};
	}
}

Item::~Item()
{

}

void Item::CollisionEvent(GameManager* gameManager)
{
	if (itemType == ITEM_TYPE_POINTBOX)
	{
		locationY = -10000;
		gameManager->getPoint(point);
		gameManager->getPower(power);
	}
	else if (itemType == ITEM_TYPE_POWERBOX)
	{
		locationY = -10000;
		gameManager->getPoint(point);
		gameManager->getPower(power);
	}
	else if (itemType == ITEM_TYPE_SHIELD)
	{
		locationY = -10000;
		gameManager->getPoint(point);
		gameManager->getPower(power);
		gameManager->getShield();
	}
}