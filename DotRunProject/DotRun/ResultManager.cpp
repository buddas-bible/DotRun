#include <string>

#include "OutputManager.h"
#include "ResultManager.h"
#include "DotRunDef.h"
#include "DataManager.h"
#include "SoundManager.h"

using namespace std;

ResultManager::ResultManager(OutputManager& out, DataManager& data) :
	outputManager(out), dataManager(data)
{

}

ResultManager::~ResultManager()
{

}


void ResultManager::init()
{
	SoundManager::getInstance().stopAllBGM();
	SoundManager::getInstance().play(SOUND_EFFECT_GAMEOVER);

	gameover = PixelObject(PIXELOBJ_GAMEOVER);
	gameover.locationX = 10;
	gameover.locationY = 10;
	messageList.clear();
	//title.Colors
	messageList.push_back(MessageObject("Press Space Bar", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 36, 15, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("Return To Menu ", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 38, 15, 1, LAYER_MESSAGEBOX));

	messageList.push_back(MessageObject("MAX SCORE :", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 40, 26, 12, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("SCORE     :", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 40, 28, 12, 1, LAYER_MESSAGEBOX));

	messageList.push_back(MessageObject("DOT    :", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 90, 26, 12, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("INCOME :", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 90, 28, 12, 1, LAYER_MESSAGEBOX));
	
	MAXSCORE = MessageObject("000000000 ", ALIGNMENT_RIGHT, COLOR_FONT_WHITE, 0, 0, 60, 26, 15, 1, LAYER_MESSAGEBOX);
	SCORE = MessageObject("000000000 ", ALIGNMENT_RIGHT, COLOR_FONT_WHITE, 0, 0, 60, 28, 15, 1, LAYER_MESSAGEBOX);

	DOT = MessageObject("000000000 ", ALIGNMENT_RIGHT, COLOR_FONT_WHITE, 0, 0, 110, 26, 15, 1, LAYER_MESSAGEBOX);
	INCOME = MessageObject("000000000 ", ALIGNMENT_RIGHT, COLOR_FONT_WHITE, 0, 0, 110, 28, 15, 1, LAYER_MESSAGEBOX);

	ResultInitializer resultinit = dataManager.getResultInit();
	DOT.SetMessage(to_string(resultinit.allDot));
	INCOME.SetMessage(to_string(resultinit.currentDot));
	SCORE.SetMessage(to_string(resultinit.currentScore));
	MAXSCORE.SetMessage(to_string(resultinit.maxScore));
}

int ResultManager::update(long long deltaTime)
{
	bool keypressedSpace = GetAsyncKeyState(VK_SPACE) & 0x0001;
	GetAsyncKeyState(VK_UP);
	GetAsyncKeyState(VK_DOWN);
	GetAsyncKeyState(VK_LEFT);
	GetAsyncKeyState(VK_RIGHT);

	if (keypressedSpace)
	{
		SoundManager::getInstance().stopAll();
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
		return CONTROL_MESSAGE_START_MENU;
	}

	return CONTROL_MESSAGE_CONTINUE;
}


void ResultManager::paint()
{
	outputManager.init();
	outputManager.paintObject(DOT);
	outputManager.paintObject(SCORE);
	outputManager.paintObject(gameover);
	outputManager.paintObject(MAXSCORE);
	outputManager.paintObject(INCOME);

	for (int i = 0; i < messageList.size(); i++) {
		outputManager.paintObject(messageList[i]);
	}

	outputManager.paintScreen();
}