#include "OutputManager.h"
#include "HowToManager.h"
#include "DotRunDef.h"
#include "SoundManager.h"

using namespace std;

HowToManager::HowToManager(OutputManager& out, DataManager& data) :
	outputManager(out), dataManager(data)
{

}

HowToManager::~HowToManager()
{

}


void HowToManager::init()
{
	SoundManager::getInstance().stopAllBGM();
	SoundManager::getInstance().play(SOUND_BGM_HOWTO);

	gameover = PixelObject(PIXELOBJ_HOWTO);
	gameover.locationX = 10;
	gameover.locationY = 10;
	messageList.clear();
	//title.Colors

	itemlist.clear();
	itemlist.push_back(Item(ITEM_TYPE_POWERBOX));
	itemlist.push_back(Item(ITEM_TYPE_SHIELD));

	itemlist[0].locationX = 11;
	itemlist[0].locationY = 25;

	itemlist[1].locationX = 11;
	itemlist[1].locationY = 27;


	messageList.clear();
	messageList.push_back(MessageObject("HOW TO PLAY", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 22, 15, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("RED DOT    : Charges the power, to use its ability.", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 15, 25, 52, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("BLUE DOT   : Obstacles can be avoided once.", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 15, 27, 50, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("POWER      : Using the space bar, dash forward", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 15, 29, 50, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("UP        : JUMP", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 100, 25, 30, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("DOWN      : SLIDE", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 100, 27, 30, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("SPACE BAR : DASH FORWARD", ALIGNMENT_LEFT, COLOR_FONT_WHITE, 0, 0, 100, 29, 30, 1, LAYER_MESSAGEBOX));
	


	

	messageList.push_back(MessageObject("Press Space Bar", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 36, 15, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("Return To Menu ", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 38, 15, 1, LAYER_MESSAGEBOX));
}

int HowToManager::update(long long deltaTime)
{
	bool keypressedSpace = GetAsyncKeyState(VK_SPACE) & 0x0001;
	GetAsyncKeyState(VK_UP);
	GetAsyncKeyState(VK_DOWN);
	GetAsyncKeyState(VK_LEFT);
	GetAsyncKeyState(VK_RIGHT);

	if (keypressedSpace)
	{
		return CONTROL_MESSAGE_START_MENU;
	}

	return CONTROL_MESSAGE_CONTINUE;
}


void HowToManager::paint()
{
	outputManager.init();
	outputManager.paintObject(DOT);
	outputManager.paintObject(SCORE);
	outputManager.paintObject(gameover);

	for (int i = 0; i < messageList.size(); i++) {
		outputManager.paintObject(messageList[i]);
	}
	for (int i = 0; i < itemlist.size(); i++) {
		outputManager.paintObject(itemlist[i]);
	}

	outputManager.paintScreen();
}