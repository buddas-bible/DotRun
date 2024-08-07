#include "Obstacle.h"
#include "GameManager.h"
#include "DotRunDef.h"

Obstacle::Obstacle(int type)
{
	if (type == OBSTACLE_TYPE_BOTTOM)
	{
		init(true, 0, GROUND_LOCATION_Y - OBSTACLE_BSIZE_Y, OBSTACLE_BSIZE_X, OBSTACLE_BSIZE_Y, LAYER_GAMEOBJECT);

		Chars.resize(OBSTACLE_BSIZE_Y, vector<char>(OBSTACLE_BSIZE_X, ' '));
		Colors.resize(OBSTACLE_BSIZE_Y, vector<int>(OBSTACLE_BSIZE_X, COLOR_BG_GRAY));
	}
	else if (type == OBSTACLE_TYPE_TOP)
	{
		init(true, 0, CEILING_LOCATION_Y + CEILING_SIZE_Y, OBSTACLE_TSIZE_X, OBSTACLE_TSIZE_Y, LAYER_GAMEOBJECT);

		Chars.resize(OBSTACLE_TSIZE_Y, vector<char>(OBSTACLE_TSIZE_X, ' '));
		Colors.resize(OBSTACLE_TSIZE_Y, vector<int>(OBSTACLE_TSIZE_X, COLOR_BG_GRAY));
	}
	else if (type == OBSTACLE_TYPE_DASH_BOTTOM)
	{
		init(true, 0, GROUND_LOCATION_Y - OBSTACLE_DBSIZE_Y, OBSTACLE_DBSIZE_X, OBSTACLE_DBSIZE_Y, LAYER_GAMEOBJECT);

		Chars.resize(OBSTACLE_DBSIZE_Y, vector<char>(OBSTACLE_DBSIZE_X, ' '));
		Colors.resize(OBSTACLE_DBSIZE_Y, vector<int>(OBSTACLE_DBSIZE_X, COLOR_BG_GRAY));
	}
}

Obstacle::~Obstacle()
{

}

void Obstacle::CollisionEvent(GameManager* gameManager)
{
	gameManager->hitPlayer(this);
}