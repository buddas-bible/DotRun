#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include "PixelObject.h"
#include "MessageObject.h"
#include "Item.h"
using namespace std;

class DataManager;

class HowToManager
{
private:
	OutputManager& outputManager;
	DataManager& dataManager;

	PixelObject gameover;
	MessageObject DOT;
	MessageObject SCORE;
public:
	HowToManager(OutputManager& out, DataManager& data);
	~HowToManager();

	vector<MessageObject> messageList;
	vector<Item> itemlist;


	void init();
	void paint();
	int update(long long);
};