#include "MenuManager.h"

#include "OutputManager.h"
#include "DotRunDef.h"
#include "SoundManager.h"

MenuManager::MenuManager(OutputManager& out, DataManager& data) :
	outputManager(out), dataManager(data)
{

}


void MenuManager::init()
{
	SoundManager::getInstance().stopAllBGM();
	SoundManager::getInstance().play(SOUND_BGM_MENU);

	currentSelected = 0;

	title = PixelObject(PIXELOBJ_TITLE);
	title.locationX = 23;
	title.locationY = 10;
	messageList.clear();
	//title.Colors

	messageList.push_back(MessageObject("Game Start!!", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 30, 12, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("Game Creator", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 33, 12, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("How To Play ", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 36, 12, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("Good Bye....", ALIGNMENT_CENTER, COLOR_FONT_WHITE, 0, 0, 74, 39, 12, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("  ", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_YELLOW, COLOR_BG_YELLOW, 70, 30, 2, 1, LAYER_MESSAGEBOX));
}



// Ű�Է��� ������ ���� ����
void MenuManager::select(int value) // �Ķ���� ����
{
	currentSelected = currentSelected + value;
	
	if (currentSelected < 0) {
		currentSelected = 0;
		return;
	}
	if (currentSelected > 3) {
		currentSelected = 3;
		return;
	}

	messageList[4].locationY = 30 + currentSelected * 3;

	SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);
}

// �� �����Ӹ��� ����, deltaTime�� ���������Ӱ� ������������ �ð�����(ms)
int MenuManager::update(long long deltaTime)
{
	bool keypressedUp = (GetAsyncKeyState(VK_UP) & 0x0001);
	bool keypressedDown = (GetAsyncKeyState(VK_DOWN) & 0x0001);
	bool keypressedRight = (GetAsyncKeyState(VK_RIGHT) & 0x0001);
	bool keypressedLeft = (GetAsyncKeyState(VK_LEFT) & 0x0001);
	bool keypressedSpace = (GetAsyncKeyState(VK_SPACE) & 0x0001);

// ������ ���������� ��ǥ
// TitleLocationPick(16,23)

	// �����̽��ٸ� Ŭ������ ��
	if (keypressedSpace)
	{
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);

		// �������� GAME START ���� ��ǥ�� �°� �������, GAME START
		if (currentSelected == 0)
		{
			return CONTROL_MESSAGE_START_SETTING;
		}

		// �������� GAME Creator ���� ��ǥ�� �°� �������, GAME Creator
		if (currentSelected == 1)
		{
			return CONTROL_MESSAGE_START_CREATOR;
		}

		// �������� Good Bye... ���� ��ǥ�� �°� �������, ��
		if (currentSelected == 2)
		{
			return CONTROL_MESSAGE_START_HOWTO;
		}

		// �������� Good Bye... ���� ��ǥ�� �°� �������, ��
		if (currentSelected == 3)
		{
			return CONTROL_MESSAGE_QUIT;
		}
	}

	// UpŰ �Է� �ޱ�
	if (keypressedUp)
	{
		select(-1);
	}

	// DownŰ �Է� �ޱ�
	if (keypressedDown)
	{
		select(1);
	}

	return CONTROL_MESSAGE_CONTINUE;
}

// �� �����Ӹ��� update�Լ� ���� �� paint����, MenuManager���� �׷����ϴ� object���� ȭ�鿡 �׸��� �Լ�
void MenuManager::paint()
{
	outputManager.init();
	outputManager.paintObject(title);

	for (int i = 0; i < messageList.size(); i++) {
		outputManager.paintObject(messageList[i]);
	}

	outputManager.paintScreen();
}