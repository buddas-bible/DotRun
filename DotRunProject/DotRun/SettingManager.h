#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

#define SETTINGMENU_POINT_GAMESTART 0
#define SETTINGMENU_POINT_UPGRADE 1
#define SETTINGMENU_POINT_COSTUME 2

#define SETTING_STATE_MENU 0
#define SETTING_STATE_SELECTMOD 10
#define SETTING_STATE_COSTUME_LIST 20

#define LIST_EXIT -1
#define LIST_FAR_LEFT 0
#define LIST_FAR_RIGHT 2

#define UPGRADE_SELECT_POINT 0
#define UPGRADE_SELECT_ITEM 1
#define UPGRADE_SELECT_TIME 2

#define UPGRADE_DEFAULT 0
#define UPGRADE_MAX 10

#define MESSAGE_NOT_ENOUGH_DOT 0

#define MESSAGE_UPGRADE_SUCCESS 1
#define MESSAGE_UPGRADE_FAILED 2
#define MESSAGE_UPGRADE_IMP 3
#define MESSAGE_HAVE_IT 4

#define MESSAGE_LIFETIME 1000

#define PERCENTAGE_BASE 3
#define PERCENTAGE 1				// __PERCENTAGE + PERCENTAGE * 업그레이드
#define PRICE 100					// DOT - PRICE * 업그레이드

#define COSTUME_CATEGORY_HAT 0
#define COSTUME_CATEGORY_CLOAT 1

#define LAYER_SETTING_UPGRADE_MESSAGEBOX 250

#define COSTUME_DATA_HAT_RED 0
#define COSTUME_DATA_HAT_AQUA 1
#define COSTUME_DATA_HAT_PURPLE 2
#define COSTUME_DATA_HAT_BLUE 3

#define COSTUME_DATA_CLOAT_RED 4
#define COSTUME_DATA_CLOAT_AQUA 5
#define COSTUME_DATA_CLOAT_PURPLE 6
#define COSTUME_DATA_CLOAT_BLUE 7

class DataManager;

class SettingManager
{
private:
	OutputManager& outputManager;
	DataManager& dataManager;

	vector<long long> currentMessageTimeList;
	vector<long long> messageTimeList;

	int menuSelect = 0;
	int state = 0;
	int list = 0;
	int costumelist = 0;

	unsigned int DOT = 1000000;

	unsigned int upgradeP = 0;
	unsigned int upgradeG = 0;
	unsigned int upgradeT = 0;


	unsigned int ownCostume[8] = { };
	int putonHat;
	int putonCloak;


	void showMessage(int, long long);
	void hideMessage(long long);

	// 방향키 조작 함수
	void menu_selectUp();
	void menu_selectDown();
	void list_selectLeft();
	void list_selectRight();
	void costumelist_selectUp();
	void costumelist_selectDown();
	void costumelist_selectLeft();
	void costumelist_selectRight();

	void settingmenuPaint();
	void settingmenuDefault();
	void upgradePaint();

	void upgradeDetailmessagePaint();
	void costumePaint();
	void messageboxPaint();

	void purchase(unsigned int&);
	bool isPurchase(unsigned int&);
	bool upgradeResult(unsigned int&);
	void upgradeFunc(unsigned int&);

	void showDOT();
	void hideDOT();

	void closelistAll();

	void messageListbool(bool);
	void upgradeListbool(bool);
	void upgradeDetailmessagebool(bool);
	void costumeListbool(bool);
	void messageBoxbool(bool);


public:
	SettingManager(OutputManager& out, DataManager& data);
	~SettingManager();

	vector<MessageObject> messageList;
	vector<MessageObject> upgradeList;
	vector<MessageObject> costumeList;
	vector<MessageObject> upgradeDetailmessage;
	vector<MessageObject> costumeDetailmessage;
	vector<MessageObject> messageBox;
	vector<MessageObject> costumeSelector;
	vector<MessageObject> costumeCollection;

	MessageObject DOTp;
	MessageObject DOT_txt;
	MessageObject messegeP;
	MessageObject messegeG;
	MessageObject messegeT;

	void init();
	void paint();
	int update(long long);
};