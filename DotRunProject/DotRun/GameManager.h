#pragma once
#include <deque>
#include <cmath>
#include "DotRunDef.h"
#include "MessageObject.h"
#include "Player.h"
#include "Obstacle.h"
#include "Item.h"

class OutputManager;
class DataManager;

class GameManager
{
private:
	OutputManager& outputManager;
	DataManager& dataManager;

	MessageObject scoreBoard;
	Player player;
	PixelObject ground;
	PixelObject ceiling;
	PixelObject backGround;
	deque<Obstacle> obstacleQueue;
	deque<Item> itemQueue;

	PixelObject costumeHat;
	PixelObject costumeCloak;
	PixelObject costumeShield;

	MessageObject powerbarText;
	MessageObject powerbar;
	MessageObject powerbarBackGround;

	int power;
	float pointAmplification = 1.0;
	float itemAmplification;
	float maxPowerAmplification;
	float powerIncrementAmplification;
	double score;
	bool gameQuit;
	bool jumping = false;
	bool dashing = false;
	bool godmode = false;
	bool sliding = false;
	bool shielding = false;
	float jumpStartLocationX;

	float dashPointX;
	float dashPointY;

	float playerLocationX = 0.0f;
	float playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y;

	int triggerPoint; // triggerPoint ���� Player�� �ְų� ������ ���¸� ������ ������Ʈ�� ��ġ�� ������ ����
	int createPoint; // �������� ��������

	const int powerMin = 0;
	const int powerMax = 500;
	const int playerLeftSpace = 10; // �÷��̾� ������ �� ����
	const float playerTakeOffDist = 10.0f;
	const float playerFlyDist = 12.0f;
	const float dashDist = 30.0f;
	const float playerDashSpeed = 120.0f;

	const float speedLevel1 = 40.0f;
	const float speedLevel2 = 50.0f;
	const float speedLevel3 = 60.0f;
	const float speedLevel4 = 70.0f;
	const float speedLevel5 = 80.0f;
	float playerSpeed; // 1�ʴ� �����̴� �ȼ��� ��

	int lastkeySpace;
	int currentkeySpace;

	void gameOver();
	int createSection(int sectionNum);
	void jump();
	void dash();

public:
	GameManager(OutputManager& out, DataManager& data);
	
	void init();
	int update(long long deltaTime);
	void paint();
	void getShield();
	void getPoint(int point);
	void hitPlayer(Obstacle* hitter);
	void getPower(int _power);
	
};