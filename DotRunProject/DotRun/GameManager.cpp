#include "GameManager.h"

#include <Windows.h>
#include <string>
#include "DotRunDef.h"
#include "OutputManager.h"
#include "DataManager.h"
#include "SoundManager.h"

GameManager::GameManager(OutputManager& out, DataManager& data) :
	outputManager(out), dataManager(data), playerSpeed(speedLevel1)
{

}

void GameManager::init()
{
	SoundManager::getInstance().stopAllBGM();
	SoundManager::getInstance().play(SOUND_BGM_GAME);

	scoreBoard = MessageObject("0", ALIGNMENT_RIGHT, COLOR_FONT_BLACK, COLOR_BG_LIGHTGREEN, COLOR_BG_LIGHTGREEN, 140, 0, 20, 1, LAYER_MESSAGEBOX);
	player = Player();
	ground = PixelObject(PIXELOBJ_GROUND);
	ceiling = PixelObject(PIXELOBJ_CEILING);
	backGround = PixelObject(PIXELOBJ_BACKGROUND);

	powerbarText = MessageObject("Power", ALIGNMENT_LEFT, COLOR_FONT_BLACK, COLOR_BG_GREEN, COLOR_BG_GREEN, POWERBAR_LOCATION_X, POWERBAR_LOCATION_Y, POWERBAR_TEXT_SIZE_X, POWERBAR_SIZE_Y, LAYER_MESSAGEBOX);
	powerbar = MessageObject("", ALIGNMENT_RIGHT, COLOR_FONT_BLACK, COLOR_BG_RED, COLOR_BG_RED, POWERBAR_LOCATION_X + POWERBAR_TEXT_SIZE_X, POWERBAR_LOCATION_Y, POWERBAR_SIZE_X, POWERBAR_SIZE_Y, LAYER_MESSAGEBOX + 1);
	powerbarBackGround = MessageObject("", ALIGNMENT_RIGHT, COLOR_FONT_BLACK, COLOR_BG_GRAY, COLOR_BG_GRAY, POWERBAR_LOCATION_X + POWERBAR_TEXT_SIZE_X, POWERBAR_LOCATION_Y, POWERBAR_SIZE_X, POWERBAR_SIZE_Y, LAYER_MESSAGEBOX);

	while (!itemQueue.empty()) itemQueue.pop_front();
	while (!obstacleQueue.empty()) obstacleQueue.pop_front();
	
	GameInitializer gameinit = dataManager.getGameInit();
	itemAmplification = gameinit.itemAmplification;
	maxPowerAmplification = gameinit.maxPower;
	pointAmplification = gameinit.pointAmplification;
	powerIncrementAmplification = gameinit.powerIncrement;
	
	gameinit.costume % 0x10;

	costumeHat = PixelObject(PIXELOBJ_COSTUME_HAT_BASE + (gameinit.costume / 0x10));
	costumeHat.locationX = playerLeftSpace - 1;
	costumeCloak = PixelObject(PIXELOBJ_COSTUME_CLOAK_BASE + (gameinit.costume % 0x10));
	costumeCloak.locationX = playerLeftSpace - 6;
	costumeShield = PixelObject(PIXELOBJ_COSTUME_SHIELD_EMPTY);
	costumeShield.locationX = playerLeftSpace + 4;

	playerSpeed = speedLevel1;
	power = (float)powerMax * maxPowerAmplification;
	gameQuit = false;
	score = 0.0;
	jumping = false;
	dashing = false;
	godmode = false;
	sliding = false;
	shielding = false;
	jumpStartLocationX = 0.0f;
	playerLocationX = 0.0f;
	playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y;
	triggerPoint = 0;
	createPoint = 120;

	lastkeySpace = 0x8001;
}

// 매 프레임마다 실행, deltaTime은 현재프레임과 이전프레임의 시간차이(ms)
int GameManager::update(long long deltaTime)
{
	bool keypressedLeft = GetAsyncKeyState(VK_LEFT) & 0x8000;
	bool keypressedRight = GetAsyncKeyState(VK_RIGHT) & 0x8000;
	bool keypressedUp = GetAsyncKeyState(VK_UP) & 0x8000;
	bool keypressedDown = GetAsyncKeyState(VK_DOWN) & 0x8000;

	currentkeySpace = GetAsyncKeyState(VK_SPACE);
	bool keypressedSpace = !(bool)lastkeySpace && (currentkeySpace & 0x8000);
	lastkeySpace = currentkeySpace;

	// 이동속도 변경
	if (score >= 60000.0) playerSpeed = speedLevel5;
	else if (score >= 20000.0) playerSpeed = speedLevel4;
	else if (score >= 6000.0) playerSpeed = speedLevel3;
	else if (score >= 2000.0) playerSpeed = speedLevel2;

	// 플레이어 이동
	if (dashing) {
		playerLocationX += playerDashSpeed * ((float)deltaTime / 1000.0f);
		player.locationX = round(playerLocationX);
	}
	else {
		playerLocationX += playerSpeed * ((float)deltaTime / 1000.0f);
		player.locationX = round(playerLocationX);
	}

	// 대쉬 중
	if (dashing) {
		dash();
	}
	else {
		// 점프 중
		if (jumping) {
			jump();
		}
		else {
			// 키 입력 처리
			if (keypressedUp) {
				SoundManager::getInstance().play(SOUND_EFFECT_JUMP);
				if (sliding) {
					sliding = false;
					player.sizeY = PLAYER_SIZE_Y;
					playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y;
					player.locationY = round(playerLocationY);
				}
				jumping = true;
				jumpStartLocationX = playerLocationX;
			}
			else if (keypressedDown) {
				sliding = true;
				player.sizeY = PLAYER_SLIDING_SIZE_Y;
				playerLocationY = GROUND_LOCATION_Y - PLAYER_SLIDING_SIZE_Y;
				player.locationY = round(playerLocationY);
			}
			else {
				if (sliding) {
					sliding = false;
					player.sizeY = PLAYER_SIZE_Y;
					playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y;
					player.locationY = round(playerLocationY);
				}
			}
		}
	}

	// 대쉬
	if (keypressedSpace) {
		if (!dashing && power >= POWER_DASH) {
			SoundManager::getInstance().play(SOUND_EFFECT_DASH);
			power = max(powerMin, power - POWER_DASH);
			dashing = true;
			godmode = true;

			if (jumping)
			{
				dashPointX = playerLocationX;
				dashPointY = playerLocationY;

				if (playerLocationX < jumpStartLocationX + playerTakeOffDist + (playerFlyDist / 2.0f)) {
					jumpStartLocationX -= 2.0f * (jumpStartLocationX + playerTakeOffDist + (playerFlyDist / 2.0f) - playerLocationX);
				}

				jumpStartLocationX += dashDist;
			}
			else
			{
				dashPointX = playerLocationX;
				dashPointY = playerLocationY;
			}
		}
	}

	// 아이템 충돌 체크
	for (deque<Item>::iterator iter = itemQueue.begin(); iter != itemQueue.end(); iter++) {
		if (player.locationX + player.sizeX <= (*iter).locationX) {
			break;
		}
		else if ((*iter).locationX + (*iter).sizeX <= player.locationX) {
			continue;
		}
		else if ((*iter).locationY + (*iter).sizeY > player.locationY && player.locationY + player.sizeY > (*iter).locationY) {
			(*iter).CollisionEvent(this);
		}
		else {
			continue;
		}
	}

	// 장애물 충돌 체크
	for (deque<Obstacle>::iterator iter = obstacleQueue.begin(); iter != obstacleQueue.end(); iter++) {
		if (player.locationX + player.sizeX <= (*iter).locationX) {
			break;
		}
		else if ((*iter).locationX + (*iter).sizeX <= player.locationX) {
			continue;
		}
		else if ((*iter).locationY + (*iter).sizeY > player.locationY && player.locationY + player.sizeY > (*iter).locationY) {
			(*iter).CollisionEvent(this);
		}
		else {
			continue;
		}
	}

	// 장애물 생성
	if (triggerPoint <= playerLocationX)
	{
		// 랜덤하게 새로운 구간 생성
		int randomSection = rand() % SECTION_BASE_SIZE;
		
		int iscore = score;
		if (iscore >= 50000 || (iscore >= 10000 && (iscore % 10000) <= 2000)) {
			randomSection = (randomSection % 2) + SECTION_BASE_SIZE;
		}
		int createdSectionSize = createSection(randomSection);

		triggerPoint += createdSectionSize;
		createPoint += createdSectionSize;
	}

	// 점수
	scoreBoard.SetMessage(to_string((long long)score));

	// power
	powerbar.SetSizeX((int)round(POWERBAR_SIZE_X * ((float)power / ((float)powerMax * maxPowerAmplification))));

	// 코스튬 위치 조정
	costumeHat.locationY = player.locationY - COSTUME_HAT_SIZEY;
	costumeCloak.locationY = player.locationY + 1;
	costumeShield.locationY = player.locationY;

	// 쉴드에 따른 플레이어 색 조정
	if (shielding) {
		player.setColor(COLOR_BG_PURPLE);
	}
	else {
		player.setColor(COLOR_BG_WHITE);
	}

	if (gameQuit) {
		return CONTROL_MESSAGE_START_RESULT;
	}

	return CONTROL_MESSAGE_CONTINUE;
}

void GameManager::jump()
{
	float jumpdist = playerLocationX - jumpStartLocationX;
	if (0.0f <= jumpdist && jumpdist < playerTakeOffDist) {
		playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (playerTakeOffDist - jumpdist) * (playerTakeOffDist - jumpdist)));
	}
	else if (playerTakeOffDist <= jumpdist && jumpdist < playerFlyDist + playerTakeOffDist) {
		playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y - 10;
	}
	else if (playerFlyDist + playerTakeOffDist <= jumpdist && jumpdist < playerFlyDist + (2 * playerTakeOffDist)) {
		playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (jumpdist - (playerTakeOffDist + playerFlyDist)) * (jumpdist - (playerTakeOffDist + playerFlyDist))));
	}
	else {
		playerLocationY = GROUND_LOCATION_Y - PLAYER_SIZE_Y;
		jumping = false;
	}

	player.locationY = round(playerLocationY);
}

void GameManager::dash()
{
	float currentDashDist = playerLocationX - dashPointX;
	if (currentDashDist < dashDist) {
		playerLocationY = dashPointY;
	}
	else {
		dashing = false;
		godmode = false;
	}
}

// 매 프레임마다 update함수 실행 후 paint실행, GameManager에서 그려야하는 object들을 화면에 그리는 함수
void GameManager::paint()
{
	outputManager.init();

	// 플레이어 위치와 상관없는 오브젝트
	outputManager.paintObject(scoreBoard);
	outputManager.paintObject(ground);
	outputManager.paintObject(ceiling);
	outputManager.paintObject(backGround);
	outputManager.paintObject(powerbarText);
	outputManager.paintObject(powerbar);
	outputManager.paintObject(powerbarBackGround);

	outputManager.paintObject(costumeHat);
	outputManager.paintObject(costumeCloak);
	outputManager.paintObject(costumeShield);

	// 플레이어 위치에 따라 위치가 변하는 오브젝트들 그리기
	int playerX = player.locationX;

	outputManager.paintObject(player, playerLeftSpace - playerX);

	// 화면을 벗어난 장애물 제거
	while (!obstacleQueue.empty() && (obstacleQueue.front().locationX + obstacleQueue.front().sizeX + playerLeftSpace - playerX < 0))
	{
		obstacleQueue.pop_front();
	}

	for (deque<Obstacle>::iterator iter = obstacleQueue.begin(); iter != obstacleQueue.end(); iter++)
	{
		// 화면 안의 장애물 출력
		if ((*iter).locationX + playerLeftSpace - playerX < SCREEN_SIZE_X)
		{
			outputManager.paintObject(*iter, playerLeftSpace - playerX);
		}
		else {
			break;
		}
	}
	
	// 화면을 벗어난 아이템 제거
	while (!itemQueue.empty() && (itemQueue.front().locationX + itemQueue.front().sizeX + playerLeftSpace - playerX < 0))
	{
		itemQueue.pop_front();
	}

	for (deque<Item>::iterator iter = itemQueue.begin(); iter != itemQueue.end(); iter++)
	{
		if ((*iter).locationX + playerLeftSpace - playerX < SCREEN_SIZE_X)
		{
			outputManager.paintObject(*iter, playerLeftSpace - playerX);
		}
		else {
			break;
		}
	}

	outputManager.paintScreen();
}

// 장애물과 아이템 생성, 생성된 구간의 길이를 리턴한다.
int GameManager::createSection(int sectionNum)
{
	int sectionSize = 0;

	if (sectionNum == SECTION_BBT)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (3 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (5 * SECTION_SAFE_SPACE) + (2 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_SAFE_SPACE) + (2 * OBSTACLE_BSIZE_X) + OBSTACLE_TSIZE_X;

		// 아이템 생성
		int positionB1 = (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionB2 = (3 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionT1 = (5 * SECTION_SAFE_SPACE) + (2 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubB = min(abs(itemlocationX - positionB1), abs(itemlocationX - positionB2));
			float mindistsubT = abs(itemlocationX - positionT1);
			
			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}
	else if (sectionNum == SECTION_BTB)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (3 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_SAFE_SPACE) + (2 * OBSTACLE_BSIZE_X) + OBSTACLE_TSIZE_X;

		// 아이템 생성
		int positionB1 = (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionT1 = (3 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);
		int positionB2 = (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubB = min(abs(itemlocationX - positionB1), abs(itemlocationX - positionB2));
			float mindistsubT = abs(itemlocationX - positionT1);

			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}
	else if (sectionNum == SECTION_TBB)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (3 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_SAFE_SPACE) + (2 * OBSTACLE_BSIZE_X) + OBSTACLE_TSIZE_X;

		// 아이템 생성
		int positionT1 = (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);
		int positionB1 = (3 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionB2 = (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubB = min(abs(itemlocationX - positionB1), abs(itemlocationX - positionB2));
			float mindistsubT = abs(itemlocationX - positionT1);

			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}
	else if (sectionNum == SECTION_TTB)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (3 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (5 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (2 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (2 * OBSTACLE_TSIZE_X);

		// 아이템 생성
		int positionT1 = (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);
		int positionT2 = (3 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);
		int positionB1 = (5 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (2 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubT = min(abs(itemlocationX - positionT1), abs(itemlocationX - positionT2));
			float mindistsubB = abs(itemlocationX - positionB1);

			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}
	else if (sectionNum == SECTION_TBT)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (3 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (2 * OBSTACLE_TSIZE_X);

		// 아이템 생성
		int positionT1 = (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);
		int positionB1 = (3 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionT2 = (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubT = min(abs(itemlocationX - positionT1), abs(itemlocationX - positionT2));
			float mindistsubB = abs(itemlocationX - positionB1);

			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}
	else if (sectionNum == SECTION_BTT)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (3 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (2 * OBSTACLE_TSIZE_X);

		// 아이템 생성
		int positionB1 = (1 * SECTION_SAFE_SPACE) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionT1 = (3 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);
		int positionT2 = (5 * SECTION_SAFE_SPACE) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubT = min(abs(itemlocationX - positionT1), abs(itemlocationX - positionT2));
			float mindistsubB = abs(itemlocationX - positionB1);

			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}
	else if (sectionNum == SECTION_HARDSECTION_DBBT)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_DASH_BOTTOM);
		obstacle.locationX = createPoint + (1 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (3 * SECTION_HARD_SAFE_SPACE) + (1 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (5 * SECTION_HARD_SAFE_SPACE) + (1 * OBSTACLE_DBSIZE_X) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_HARD_SAFE_SPACE) + (1 * OBSTACLE_DBSIZE_X) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);

		// 아이템 생성
		int positionDB = (1 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_DBSIZE_X / 2);
		int positionB = (3 * SECTION_HARD_SAFE_SPACE) + (1 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionT = (5 * SECTION_HARD_SAFE_SPACE) + (1 * OBSTACLE_DBSIZE_X) + (1 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubB = min(abs(itemlocationX - positionB), abs(itemlocationX - positionDB));
			float mindistsubT = abs(itemlocationX - positionT);

			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}
	else if (sectionNum == SECTION_HARDSECTION_TBDB)
	{
		// 장애물 생성
		Obstacle obstacle = Obstacle(OBSTACLE_TYPE_TOP);
		obstacle.locationX = createPoint + (1 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_BOTTOM);
		obstacle.locationX = createPoint + (3 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		obstacle = Obstacle(OBSTACLE_TYPE_DASH_BOTTOM);
		obstacle.locationX = createPoint + (5 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);
		obstacleQueue.push_back(obstacle);

		// return할 값 대입
		sectionSize = (6 * SECTION_HARD_SAFE_SPACE) + (1 * OBSTACLE_DBSIZE_X) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X);

		// 아이템 생성
		int positionT = (1 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (0 * OBSTACLE_TSIZE_X) + (OBSTACLE_TSIZE_X / 2);
		int positionB = (3 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (0 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_BSIZE_X / 2);
		int positionDB = (5 * SECTION_HARD_SAFE_SPACE) + (0 * OBSTACLE_DBSIZE_X) + (1 * OBSTACLE_BSIZE_X) + (1 * OBSTACLE_TSIZE_X) + (OBSTACLE_DBSIZE_X / 2);

		for (int i = 0; i * 5 < sectionSize; i++) {
			Item item = Item(ITEM_TYPE_POINTBOX);
			int ran = rand() % 1000;
			if (ran < ITEM_POWERBOX_APPEARANCE_PROBABILITY * itemAmplification) {
				item = Item(ITEM_TYPE_POWERBOX);
			}
			else if (ran < (ITEM_POWERBOX_APPEARANCE_PROBABILITY + ITEM_SHIELD_APPEARANCE_PROBABILITY) * itemAmplification)
			{
				item = Item(ITEM_TYPE_SHIELD);
			}
			int itemlocationX = i * 5;

			float mindistsubB = min(abs(itemlocationX - positionB), abs(itemlocationX - positionDB));
			float mindistsubT = abs(itemlocationX - positionT);

			if (mindistsubB < (playerFlyDist / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4 - 10.0f;
			}
			else if (mindistsubB < (playerFlyDist / 2) + playerTakeOffDist) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = round(GROUND_LOCATION_Y - 4 - (10.0f - ((10.0f / (playerTakeOffDist * playerTakeOffDist)) * (mindistsubB - (playerFlyDist / 2)) * (mindistsubB - (playerFlyDist / 2)))));
			}
			else if (mindistsubT <= (OBSTACLE_TSIZE_X / 2)) {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 2;
			}
			else {
				item.locationX = createPoint + itemlocationX;
				item.locationY = GROUND_LOCATION_Y - 4;
			}

			itemQueue.push_back(item);
		}
	}

	return sectionSize;
}

void GameManager::getPoint(int point)
{
	score += pointAmplification * point;
}

void GameManager::gameOver()
{
	dataManager.gameOverHandling(score);
	gameQuit = true;
}

void GameManager::getShield()
{
	shielding = true;
}

void GameManager::getPower(int _power)
{
	power += ((float)_power * powerIncrementAmplification);
	if (power > (powerMax * maxPowerAmplification)) {
		power = (powerMax * maxPowerAmplification);
	}
}

void GameManager::hitPlayer(Obstacle* hitter)
{
	if (godmode) {
		hitter->locationY = -10000;
		SoundManager::getInstance().play(SOUND_EFFECT_BREAK);
	}
	else if (shielding) {
		hitter->locationY = -10000;
		shielding = false;
		SoundManager::getInstance().play(SOUND_EFFECT_BREAK);
	}
	else {
		gameOver();
	}
}