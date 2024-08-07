#pragma warning(disable:4996)

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "DotRunDef.h"
#include "MessageObject.h"
#include "OutputManager.h"
#include "SettingManager.h"
#include "DataManager.h"
#include "SoundManager.h"

using namespace std;

SettingManager::SettingManager(OutputManager& out, DataManager& data) :
	outputManager(out), dataManager(data)
{

}

SettingManager::~SettingManager()
{

}


void SettingManager::menu_selectUp()
{
	if (menuSelect != 0)
	{
		menuSelect--;
		messageList[3].locationY = 3 * menuSelect + 12;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}

void SettingManager::menu_selectDown()
{
	if (menuSelect != 2)
	{
		menuSelect++;
		messageList[3].locationY = 3 * menuSelect + 12;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}

void SettingManager::list_selectLeft()
{
	if (list != -1)
	{
		--list;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}

void SettingManager::list_selectRight()
{
	if (list != 2)
	{
		++list;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}


void SettingManager::costumelist_selectUp()
{
	if (costumelist > 3 )
	{
		costumelist -= 4;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}

void SettingManager::costumelist_selectDown()
{
	if (costumelist < 4)
	{
		costumelist += 4;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}

void SettingManager::costumelist_selectLeft()
{
	if (costumelist == 4)
	{
		costumelist = -1;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
	else if (costumelist != -1)
	{
		--costumelist;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}

void SettingManager::costumelist_selectRight()
{
	if (costumelist == 3 || costumelist == 7)
	{
		costumelist;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
	else
	{
		++costumelist;
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
	}
}


void SettingManager::init()
{
	SoundManager::getInstance().stopAllBGM();
	SoundManager::getInstance().play(SOUND_BGM_SETTING);

	SettingInitializer settinginit = dataManager.getSettingInit();
	upgradeP = settinginit.upgradeP;
	upgradeG = settinginit.upgradeG;
	upgradeT = settinginit.upgradeT;
	for (int i = 0; i < 8; i++) {
		ownCostume[i] = settinginit.costume[i];
	}

	ResultInitializer resultinit = dataManager.getResultInit();
	DOT = resultinit.allDot;

	GameInitializer gameinit = dataManager.getGameInit();
	putonHat = gameinit.costume / 0x10;
	putonCloak = gameinit.costume % 0x10;

	// 문자열 , 정렬 , 글
	messageList.clear();
	messageList.push_back(MessageObject("GAME START", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, SCREEN_SIZE_X / 2 - 6, 12, 12, 3, LAYER_SETTINGMENU));
	messageList.push_back(MessageObject("UPGRADE", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, SCREEN_SIZE_X / 2 - 6, 15, 12, 3, LAYER_SETTINGMENU));
	messageList.push_back(MessageObject("COSTUME", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, SCREEN_SIZE_X / 2 - 6, 18, 12, 3, LAYER_SETTINGMENU));
	messageList.push_back(MessageObject("  ", ALIGNMENT_LEFT, COLOR_FONT_BLACK, COLOR_BG_YELLOW, COLOR_BG_BLACK, 70, 12, 2, 3, LAYER_SETTINGMENU));
	messageListbool(true);

	// 선택하면 해당 레이어가 꺼지는 방식으로 함.
	upgradeList.clear();
	upgradeList.push_back(MessageObject("POINT++", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 35, 7, 23, 11, LAYER_SETTINGLIST_SELECT));
	upgradeList.push_back(MessageObject("POWER++", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 75, 7, 23, 11, LAYER_SETTINGLIST_SELECT));
	upgradeList.push_back(MessageObject("ITEM++", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 115, 7, 23, 11, LAYER_SETTINGLIST_SELECT));
	upgradeList.push_back(MessageObject("POINT++", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 35, 7, 23, 11, LAYER_SETTINGLIST));
	upgradeList.push_back(MessageObject("POWER++", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 75, 7, 23, 11, LAYER_SETTINGLIST));
	upgradeList.push_back(MessageObject("ITEM++", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 115, 7, 23, 11, LAYER_SETTINGLIST));
	upgradeListbool(false);
	 
	upgradeDetailmessage.clear();
	upgradeDetailmessage.push_back(MessageObject("Increase point acquisition.", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 35, 30, 104, 11, LAYER_SETTINGLIST_SELECT));
	upgradeDetailmessage.push_back(MessageObject("Increase the probability of item appearance.", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 35, 30, 104, 11, LAYER_SETTINGLIST_SELECT));
	upgradeDetailmessage.push_back(MessageObject("Increase dash gauge acquisition.", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 35, 30, 104, 11, LAYER_SETTINGLIST_SELECT));
	upgradeDetailmessagebool(false);

	costumeList.clear();
	costumeList.push_back(MessageObject("RED HAT", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 35, 7, 21, 11, LAYER_SETTINGLIST_SELECT));
	costumeList.push_back(MessageObject("AQUA HAT", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 61, 7, 21, 11, LAYER_SETTINGLIST_SELECT));
	costumeList.push_back(MessageObject("PURPLE HAT", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 87, 7, 21, 11, LAYER_SETTINGLIST_SELECT));
	costumeList.push_back(MessageObject("BLUE HAT", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 113, 7, 21, 11, LAYER_SETTINGLIST_SELECT));
	costumeList.push_back(MessageObject("RED CLOAK", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 35, 30, 21, 11, LAYER_SETTINGLIST_SELECT));
	costumeList.push_back(MessageObject("AQUA CLOAK", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 61, 30, 21, 11, LAYER_SETTINGLIST_SELECT));
	costumeList.push_back(MessageObject("PURPLE CLOAK", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 87, 30, 21, 11, LAYER_SETTINGLIST_SELECT));
	costumeList.push_back(MessageObject("BLUE CLOAK", ALIGNMENT_CENTER, COLOR_FONT_GRAY, COLOR_BG_BLACK, COLOR_BG_GRAY, 113, 30, 21, 11, LAYER_SETTINGLIST_SELECT));

	costumeList.push_back(MessageObject("RED HAT", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 35, 7, 21, 11, LAYER_SETTINGLIST));
	costumeList.push_back(MessageObject("AQUA HAT", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 61, 7, 21, 11, LAYER_SETTINGLIST));
	costumeList.push_back(MessageObject("PURPLE HAT", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 87, 7, 21, 11, LAYER_SETTINGLIST));
	costumeList.push_back(MessageObject("BLUE HAT", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 113, 7, 21, 11, LAYER_SETTINGLIST));
	costumeList.push_back(MessageObject("RED CLOAK", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 35, 30, 21, 11, LAYER_SETTINGLIST));
	costumeList.push_back(MessageObject("AQUA CLOAK", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 61, 30, 21, 11, LAYER_SETTINGLIST));
	costumeList.push_back(MessageObject("PURPLE CLOAK", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 87, 30, 21, 11, LAYER_SETTINGLIST));
	costumeList.push_back(MessageObject("BLUE CLOAK", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 113, 30, 21, 11, LAYER_SETTINGLIST));
	costumeListbool(false);

	costumeDetailmessage.clear();
	costumeDetailmessage.push_back(MessageObject("Increase point acquisition.", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_YELLOW, 35, 30, 104, 11, LAYER_SETTINGLIST_SELECT));

	messageBox.clear();
	messageBox.push_back(MessageObject("NOT ENOUGH DOT '^' ", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_WHITE, 52, 12, 70, 25, LAYER_SETTING_UPGRADE_MESSAGEBOX));
	messageBox.push_back(MessageObject("UPGRADE SUCCESS!!!", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_GREEN, 52, 12, 70, 25, LAYER_SETTING_UPGRADE_MESSAGEBOX));
	messageBox.push_back(MessageObject("UPGRADE FAILED...", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_RED, 52, 12, 70, 25, LAYER_SETTING_UPGRADE_MESSAGEBOX));
	messageBox.push_back(MessageObject("REACHED THE MAX LEVEL", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_WHITE, 52, 12, 70, 25, LAYER_SETTING_UPGRADE_MESSAGEBOX));
	messageBox.push_back(MessageObject("HAVE IT", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_WHITE, 35, 21, 104, 8, LAYER_SETTING_UPGRADE_MESSAGEBOX));
	messageBoxbool(false);

	costumeSelector.clear();
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 37, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 10));
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 63, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 10));
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 89, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 10));
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 115, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 10));
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 37, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 10));
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 63, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 10));
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 89, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 10));
	costumeSelector.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_LIGHTPURPLE, 115, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 10));

	for (int i = 0; i < costumeSelector.size(); i++) {
		costumeSelector[i].setVisible(false);
	}

	costumeCollection.clear();
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 37, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 5));
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 63, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 5));
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 89, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 5));
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 115, 16, 17, 1, LAYER_SETTINGLIST_SELECT + 5));
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 37, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 5));
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 63, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 5));
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 89, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 5));
	costumeCollection.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_FONT_WHITE + COLOR_BG_WHITE, COLOR_BG_WHITE, 115, 39, 17, 1, LAYER_SETTINGLIST_SELECT + 5));

	for (int i = 0; i < costumeCollection.size(); i++) {
		costumeCollection[i].setVisible(false);
	}

	messageTimeList.resize(messageBox.size(), 0ll);
	currentMessageTimeList.resize(messageBox.size(), 0ll);

	DOT_txt = MessageObject("DOT", ALIGNMENT_LEFT, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 17, 33, 7, 3, LAYER_SETTING_MESSAGEBOX);
	DOTp = MessageObject(to_string(DOT), ALIGNMENT_LEFT, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 10, 33, 7, 3, LAYER_SETTING_MESSAGEBOX);
	hideDOT();

	messegeP = MessageObject(to_string(upgradeP), ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 43, 23, 7, 3, LAYER_SETTINGLIST_SELECT);
	messegeG = MessageObject(to_string(upgradeG), ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 83, 23, 7, 3, LAYER_SETTINGLIST_SELECT);
	messegeT = MessageObject(to_string(upgradeT), ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 123, 23, 7, 3, LAYER_SETTINGLIST_SELECT);
}


// time은 (ms단위)
void SettingManager::showMessage(int messageNumber, long long time)
{
	messageBox[messageNumber].setVisible(true);
	currentMessageTimeList[messageNumber] = 0ll;
	messageTimeList[messageNumber] = time;
}

void SettingManager::hideMessage(long long deltaTime)
{
	for (int i = 0; i < messageTimeList.size(); i++) {
		currentMessageTimeList[i] += deltaTime;
		if (currentMessageTimeList[i] > messageTimeList[i]) {
			messageBox[i].setVisible(false);
		}
	}
}

void SettingManager::showDOT()
{
	DOT_txt.setVisible(true);
	DOTp.setVisible(true);
	DOTp.SetMessage(to_string(DOT));
}

void SettingManager::hideDOT()
{
	DOT_txt.setVisible(false);
	DOTp.setVisible(false);
	DOTp.SetMessage(to_string(DOT));
}


int SettingManager::update(long long deltaTime)
{
	bool keypressedUp = GetAsyncKeyState(VK_UP) & 0x0001;
	bool keypressedDown = GetAsyncKeyState(VK_DOWN) & 0x0001;
	bool keypressedLeft = GetAsyncKeyState(VK_LEFT) & 0x0001;
	bool keypressedRight = GetAsyncKeyState(VK_RIGHT) & 0x0001;
	bool keypressedSpace = GetAsyncKeyState(VK_SPACE) & 0x0001;


	// 세팅 메뉴 선택
	if (state == SETTING_STATE_MENU)
	{
		if (keypressedUp)
		{
			menu_selectUp();
		}
		else if (keypressedDown)
		{ 
			menu_selectDown();
		}
		else if (keypressedSpace)
		{
			state = SETTING_STATE_SELECTMOD;
			SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
		}
	}

	// 메뉴에서 뭐든 선택한 상태
	else if (state == SETTING_STATE_SELECTMOD)
	{
		// 뭐든 선택했는데 그게 게임시작이면 게임 시작.
		if (menuSelect == SETTINGMENU_POINT_GAMESTART)
		{
			settingmenuDefault();
			return CONTROL_MESSAGE_START_GAME;
		}

		// 업그레이드 선택 시
		if (menuSelect == SETTINGMENU_POINT_UPGRADE)
		{
			// 리스트에서 방향키 왼쪽을 누르면 나감
			if (list == LIST_EXIT)
			{
				settingmenuDefault();
			}
			if (keypressedLeft)
			{
				list_selectLeft();
			}
			else if (keypressedRight)
			{
				list_selectRight();
			}
			else if (keypressedSpace)
			{
				SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
				if (list == UPGRADE_SELECT_POINT)
				{
					upgradeFunc(upgradeP);
				}
				else if (list == UPGRADE_SELECT_ITEM)
				{
					upgradeFunc(upgradeG);
				}
				else if (list == UPGRADE_SELECT_TIME)
				{
					upgradeFunc(upgradeT);
				}
			}
		}
		// 코스튬 메뉴 선택 시
		else if (menuSelect == SETTINGMENU_POINT_COSTUME)
		{
			// 리스트에서 방향키 왼쪽을 누르면 나감
			if (costumelist == LIST_EXIT)
			{
				settingmenuDefault();
			}
			if (keypressedLeft)
			{
				costumelist_selectLeft();
			}
			else if (keypressedRight)
			{
				costumelist_selectRight();
			}
			else if (keypressedUp)
			{
				costumelist_selectUp();
			}
			else if (keypressedDown)
			{
				costumelist_selectDown();
			}
			else if (keypressedSpace)
			{
				SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
				if (ownCostume[costumelist] == 0)
				{
					// 가지고 있는 코스튬 데이터가 0이면 돈 체크
					if (DOT > PRICE)
					{
						DOT = DOT - PRICE;
						++ownCostume[costumelist];
					}
					else
					{
						// 돈이 부족하다 알림
						showMessage(MESSAGE_NOT_ENOUGH_DOT, MESSAGE_LIFETIME);
					}
				}
				else
				{
					if (costumelist > -1 && costumelist < 4)
					{
						if (putonHat == costumelist) {
							putonHat = 0xf;
						}
						else {
							putonHat = costumelist;
						}
					}
					if (costumelist > 3 && costumelist < 8)
					{
						if (putonCloak == costumelist) {
							putonCloak = 0xf;
						}
						else {
							putonCloak = costumelist;
						}
					}
				}
				dataManager.costumeHandling(ownCostume[0], ownCostume[1], ownCostume[2], ownCostume[3], ownCostume[4], ownCostume[5], ownCostume[6], ownCostume[7], DOT, putonHat * 0x10 + putonCloak);
			}
		}
	}

	closelistAll();
	if (state == 0)
	{
		messageListbool(true);
	}
	else if (state == 10 && menuSelect == 1)
	{
		messageListbool(true);
		messageList[0].locationX = 10;
		messageList[1].locationX = 10;
		messageList[2].locationX = 10;
		messageList[3].locationX = 7;
		upgradeListbool(true);
		messageBoxbool(true);
		messegeP.setVisible(true);
		messegeG.setVisible(true);
		messegeT.setVisible(true);
		messegeP.SetMessage(to_string(upgradeP));
		messegeG.SetMessage(to_string(upgradeG));
		messegeT.SetMessage(to_string(upgradeT));
		upgradeDetailmessagebool(false);
		if (list != -1)
		{
			upgradeList[list].setVisible(false);
			upgradeDetailmessage[list].setVisible(true);
		}
	}
	else if (state == 10 && menuSelect == 2)
	{
		messageListbool(true);
		messageList[0].locationX = 10;
		messageList[1].locationX = 10;
		messageList[2].locationX = 10;
		messageList[3].locationX = 7;
		costumeListbool(true);
		messageBoxbool(true);
		if (costumelist != -1)
		{
			costumeList[costumelist].setVisible(false);
		}

		if (putonHat != 0xf) {
			costumeSelector[putonHat].setVisible(true);
		}
		if (putonCloak != 0xf) {
			costumeSelector[putonCloak].setVisible(true);
		}

		for (int i = 0; i < 8; i++) {
			costumeCollection[i].setVisible(ownCostume[i]);
		}
	}

	if (state != SETTING_STATE_MENU)
	{
		showDOT();
	}
	else
	{
		hideDOT();
	}

	hideMessage(deltaTime);

	return CONTROL_MESSAGE_CONTINUE;
}


void SettingManager::paint()
{
	outputManager.init();

	settingmenuPaint();

	upgradePaint();

	upgradeDetailmessagePaint();

	costumePaint();

	messageboxPaint();

	for (int i = 0; i < costumeSelector.size(); i++) {
		outputManager.paintObject(costumeSelector[i]);
	}
	
	for (int i = 0; i < costumeCollection.size(); i++) {
		outputManager.paintObject(costumeCollection[i]);
	}

	outputManager.paintObject(DOTp);
	outputManager.paintObject(DOT_txt);

	outputManager.paintObject(messegeP);
	outputManager.paintObject(messegeG);
	outputManager.paintObject(messegeT);

	outputManager.paintScreen();
}


void SettingManager::settingmenuPaint()
{
	for (int i = 0; i < messageList.size(); i++)
	{
		outputManager.paintObject(messageList[i]);
	}
}

void SettingManager::settingmenuDefault()
{
	messageList[0].locationX = SCREEN_SIZE_X / 2 - 6;
	messageList[1].locationX = SCREEN_SIZE_X / 2 - 6;
	messageList[2].locationX = SCREEN_SIZE_X / 2 - 6;
	messageList[3].locationX = 70;
	state = 0;
	list = 0;
	costumelist = 0;
}



void SettingManager::upgradePaint()
{
	for (int i = 0; i < upgradeList.size(); i++)
	{
		outputManager.paintObject(upgradeList[i]);
	}
}

// void SettingManager::

void SettingManager::upgradeDetailmessagePaint()
{
	for (int i = 0; i < upgradeDetailmessage.size(); i++)
	{
		outputManager.paintObject(upgradeDetailmessage[i]);
	}
}

void SettingManager::costumePaint()
{
	for (int i = 0; i < costumeList.size(); i++)
	{
		outputManager.paintObject(costumeList[i]);
	}
}

void SettingManager::messageboxPaint()
{
	for (int i = 0; i < messageBox.size(); i++)
	{
		outputManager.paintObject(messageBox[i]);
	}
}


void SettingManager::purchase(unsigned int& upgradeValue)
{
	DOT = DOT - (PRICE * upgradeValue);
 }

bool SettingManager::isPurchase(unsigned int& upgradeValue)
{
	return DOT > (PRICE * upgradeValue);
}

bool SettingManager::upgradeResult(unsigned int& upgradeValue)
{
	return (rand() % (PERCENTAGE_BASE + (PERCENTAGE * upgradeValue)) == 1);
}

void SettingManager::upgradeFunc(unsigned int& upgradeValue)
{
	if (isPurchase(upgradeValue))
	{
		if (upgradeValue < UPGRADE_MAX)
		{
			if (upgradeResult(upgradeValue))
			{
				++upgradeValue;
				purchase(upgradeValue);
				showMessage(MESSAGE_UPGRADE_SUCCESS, MESSAGE_LIFETIME);
			}
			else
			{
				purchase(upgradeValue);
				showMessage(MESSAGE_UPGRADE_FAILED, MESSAGE_LIFETIME);
			}

			// 저장
			dataManager.upgradeHandling(upgradeP, upgradeG, upgradeT, DOT);
		}
		else
		{
			showMessage(MESSAGE_UPGRADE_IMP, MESSAGE_LIFETIME);
		}
	}
	else
	{
		showMessage(MESSAGE_NOT_ENOUGH_DOT, MESSAGE_LIFETIME);
	}
}



void SettingManager::closelistAll()
{
	messageListbool(false);
	upgradeListbool(false);
	upgradeDetailmessagebool(false);
	costumeListbool(false);
	messageBoxbool(false);
	messegeP.setVisible(false);
	messegeG.setVisible(false);
	messegeT.setVisible(false);

	for (int i = 0; i < costumeSelector.size(); i++) {
		costumeSelector[i].setVisible(false);
	}
	
	for (int i = 0; i < costumeCollection.size(); i++) {
		costumeCollection[i].setVisible(false);
	}
}


void SettingManager::messageListbool(bool _is)
{
	for (int i = 0; i < messageList.size(); i++)
	{
		messageList[i].setVisible(_is);
	}
}

void SettingManager::upgradeListbool(bool _is)
{
	for (int i = 0; i < upgradeList.size(); i++)
	{
		upgradeList[i].setVisible(_is);
	}
}

void SettingManager::upgradeDetailmessagebool(bool _is)
{
	for (int i = 0; i < upgradeDetailmessage.size(); i++)
	{
		upgradeDetailmessage[i].setVisible(_is);
	}
}

/*
void SettingManager::upgradeprintf(int list)
{
	for (int i = 0; i < upgradeDetailmessage.size(); i++)
	{
		upgradeDetailmessage[i].setVisible(i == list);
	}
}
*/

void SettingManager::costumeListbool(bool _is)
{
	for (int i = 0; i < costumeList.size(); i++)
	{
		costumeList[i].setVisible(_is);
	}
}

void SettingManager::messageBoxbool(bool _is)
{
	for (int i = 0; i < messageBox.size(); i++)
	{
		messageBox[i].setVisible(_is);
	}
}

