#include "Player.h"
#include "DotRunDef.h"
#include "GameManager.h"

Player::Player()
{
	init(true, 0, GROUND_LOCATION_Y - PLAYER_SIZE_Y, PLAYER_SIZE_X, PLAYER_SIZE_Y, LAYER_PLAYER);

	Chars.resize(PLAYER_SIZE_Y, vector<char>(PLAYER_SIZE_X, ' '));
	Colors.resize(PLAYER_SIZE_Y, vector<int>(PLAYER_SIZE_X, COLOR_BG_WHITE));
}

Player::~Player()
{

}

void Player::CollisionEvent(GameManager* gameManager)
{

}