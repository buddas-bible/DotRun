#pragma once
#include <vector>
#include "MessageObject.h"
using namespace std;

class OutputManager;
class DataManager;

class MenuManager
{
private:
	DataManager& dataManager;
	OutputManager& outputManager;

	int currentSelected;
	PixelObject title;
	vector<MessageObject> messageList;

	void select(int value);

public:
	MenuManager(OutputManager& out, DataManager& data);

	void init();
	int update(long long deltaTime);
	void paint();

};
