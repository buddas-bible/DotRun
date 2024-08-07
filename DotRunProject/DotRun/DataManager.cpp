#include "DataManager.h"
#include "DotRunDef.h"

DataManager::DataManager()
{
	
}

void DataManager::init()
{
	resultInitializer.maxScore = saveManager.Read(SAVE_KEY_MAXSCORE);
	resultInitializer.allDot = saveManager.Read(SAVE_KEY_DOT);
	gameInitializer.costume = saveManager.Read(SAVE_KEY_COSTUME);
	settingInitializer.upgradeP = saveManager.Read(SAVE_KEY_UPGRADE_POINT);
	settingInitializer.upgradeG = saveManager.Read(SAVE_KEY_UPGRADE_POWER);
	settingInitializer.upgradeT = saveManager.Read(SAVE_KEY_UPGRADE_PROBABILITY);
	settingInitializer.costume[0] = saveManager.Read(SAVE_KEY_COSTUME0);
	settingInitializer.costume[1] = saveManager.Read(SAVE_KEY_COSTUME1);
	settingInitializer.costume[2] = saveManager.Read(SAVE_KEY_COSTUME2);
	settingInitializer.costume[3] = saveManager.Read(SAVE_KEY_COSTUME3);
	settingInitializer.costume[4] = saveManager.Read(SAVE_KEY_COSTUME4);
	settingInitializer.costume[5] = saveManager.Read(SAVE_KEY_COSTUME5);
	settingInitializer.costume[6] = saveManager.Read(SAVE_KEY_COSTUME6);
	settingInitializer.costume[7] = saveManager.Read(SAVE_KEY_COSTUME7);

	gameInitializer.pointAmplification = 1.0f + (float)settingInitializer.upgradeP * 0.05f;
	gameInitializer.maxPower = 1.0f + (float)settingInitializer.upgradeG * 0.1f;
	gameInitializer.powerIncrement = 1.0f + (float)settingInitializer.upgradeG * 0.1f;
	gameInitializer.itemAmplification = 1.0f + (float)settingInitializer.upgradeT * 0.05f;
}

GameInitializer DataManager::getGameInit()
{
	return gameInitializer;
}

void DataManager::setGameInit(float _pointAmplification, float _maxPower, float _powerIncrement, float _itemAppearanceProbability)
{
	gameInitializer.pointAmplification = _pointAmplification;
	gameInitializer.maxPower = _maxPower;
	gameInitializer.powerIncrement = _powerIncrement;
	gameInitializer.itemAmplification = _itemAppearanceProbability;
}

ResultInitializer DataManager::getResultInit()
{
	return resultInitializer;
}

void DataManager::gameOverHandling(double _score)
{
	int maxScore = saveManager.Read(SAVE_KEY_MAXSCORE);
	if (maxScore < _score) {
		resultInitializer.maxScore = _score;
	}
	else {
		resultInitializer.maxScore = maxScore;
	}
	
	resultInitializer.currentScore = _score;
	resultInitializer.allDot = saveManager.Read(SAVE_KEY_DOT) + _score * 0.5;
	resultInitializer.currentDot = _score * 0.5;

	saveManager.DataSave(SAVE_KEY_MAXSCORE, resultInitializer.maxScore);
	saveManager.DataSave(SAVE_KEY_DOT, resultInitializer.allDot);

	saveManager.Write();
}

void DataManager::upgradeHandling(int upgradeP, int upgradeG, int upgradeT, int dot)
{
	saveManager.DataSave(SAVE_KEY_UPGRADE_POINT, upgradeP);
	saveManager.DataSave(SAVE_KEY_UPGRADE_POWER, upgradeG);
	saveManager.DataSave(SAVE_KEY_UPGRADE_PROBABILITY, upgradeT);
	saveManager.DataSave(SAVE_KEY_DOT, dot);

	settingInitializer.upgradeP = upgradeP;
	settingInitializer.upgradeG = upgradeG;
	settingInitializer.upgradeT = upgradeT;
	resultInitializer.allDot = dot;

	gameInitializer.pointAmplification = 1.0f + (float)settingInitializer.upgradeP * 0.05f;
	gameInitializer.maxPower = 1.0f + (float)settingInitializer.upgradeG * 0.1f;
	gameInitializer.powerIncrement = 1.0f + (float)settingInitializer.upgradeG * 0.1f;
	gameInitializer.itemAmplification = 1.0f + (float)settingInitializer.upgradeT * 0.05f;

	saveManager.Write();
}

void DataManager::costumeHandling(int c0, int c1, int c2, int c3, int c4, int c5, int c6, int c7, int dot, int puton)
{
	settingInitializer.costume[0] = c0;
	settingInitializer.costume[1] = c1;
	settingInitializer.costume[2] = c2;
	settingInitializer.costume[3] = c3;
	settingInitializer.costume[4] = c4;
	settingInitializer.costume[5] = c5;
	settingInitializer.costume[6] = c6;
	settingInitializer.costume[7] = c7;
	saveManager.DataSave(SAVE_KEY_COSTUME0, c0);
	saveManager.DataSave(SAVE_KEY_COSTUME1, c1);
	saveManager.DataSave(SAVE_KEY_COSTUME2, c2);
	saveManager.DataSave(SAVE_KEY_COSTUME3, c3);
	saveManager.DataSave(SAVE_KEY_COSTUME4, c4);
	saveManager.DataSave(SAVE_KEY_COSTUME5, c5);
	saveManager.DataSave(SAVE_KEY_COSTUME6, c6);
	saveManager.DataSave(SAVE_KEY_COSTUME7, c7);

	resultInitializer.allDot = dot;
	gameInitializer.costume = puton;
	saveManager.DataSave(SAVE_KEY_DOT, dot);
	saveManager.DataSave(SAVE_KEY_COSTUME, puton);

	saveManager.Write();
}

SettingInitializer DataManager::getSettingInit()
{
	return settingInitializer;
}

void DataManager::setSettingInit(int _upgradeP, int _upgradeG, int _upgradeT)
{
	settingInitializer.upgradeP = _upgradeP;
	settingInitializer.upgradeG = _upgradeG;
	settingInitializer.upgradeT = _upgradeT;
}