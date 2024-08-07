#include <iostream>
#include <string>
#include <vector>
#include "windows.h"

using namespace std;

class GameManeger
{
	int player;
	int list_obstacle;
	int list_item;
	int period_obstacle;
	int period_item;

	int update(float deltatime) { }
	void paintAllObject();
};