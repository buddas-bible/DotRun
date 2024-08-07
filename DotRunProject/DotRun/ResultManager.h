#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "PixelObject.h"
#include "MessageObject.h"
using namespace std;

class DataManager;

class ResultManager
{
private:
	OutputManager& outputManager;
	DataManager& dataManager;

	PixelObject gameover;
	MessageObject DOT;
	MessageObject SCORE;
	MessageObject MAXSCORE;
	MessageObject INCOME;
public:
	ResultManager(OutputManager& out, DataManager& data);
	~ResultManager();

	vector<MessageObject> messageList;

	void init();
	void paint();
	int update(long long);
};