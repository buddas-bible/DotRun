#pragma once

#include "SaveManager.h"

struct GameInitializer {
	float pointAmplification;
	float maxPower;
	float powerIncrement;
	float itemAmplification;
	int costume;
};

struct ResultInitializer {
	int maxScore;
	int currentScore;
	int allDot;
	int currentDot;
};

struct SettingInitializer {
	int upgradeP;
	int upgradeG;
	int upgradeT;
	int costume[8];
};

class DataManager {
private:
	GameInitializer gameInitializer;
	ResultInitializer resultInitializer;
	SettingInitializer settingInitializer;

	SaveManager saveManager;

public:
	DataManager();

	void init();

	GameInitializer getGameInit();
	void setGameInit(float, float, float, float);

	ResultInitializer getResultInit();
	void gameOverHandling(double);
	void upgradeHandling(int, int, int, int);
	void costumeHandling(int, int, int, int, int, int, int, int, int, int);

	SettingInitializer getSettingInit();
	void setSettingInit(int, int, int);
};