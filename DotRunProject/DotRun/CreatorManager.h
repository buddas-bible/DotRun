#pragma once

#include <vector>
#include "MessageObject.h"

class OutputManager;
class DataManager;

struct POS
{
	int x, y;
};

class CreatorManager
{
private:
	DataManager& dataManager;
	OutputManager& outputManager;

	vector<MessageObject> messageList;

	POS snake[100];
	POS item;
	POS footprint;
	bool gameQuit;
	int dir = -1;
	int len = 2;
	int score = 0;
	long long timecheck;
	const long long period = 250;

	const int scoreShowTeam = 20;
	const int scoreShowName0 = 40;
	const int scoreShowName1 = 60;
	const int scoreShowName2 = 80;
	const int scoreShowSpecial = 100;

	void snakegameover();
	void move_snake(POS* snake, int len);

public:
	CreatorManager(OutputManager& out, DataManager& data);

	void init();
	int update(long long deltaTime);
	void paint();
};