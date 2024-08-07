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



// 키입력이 들어오면 변경 관련
void MenuManager::select(int value) // 파라미터 설정
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

// 매 프레임마다 실행, deltaTime은 현재프레임과 이전프레임의 시간차이(ms)
int MenuManager::update(long long deltaTime)
{
	bool keypressedUp = (GetAsyncKeyState(VK_UP) & 0x0001);
	bool keypressedDown = (GetAsyncKeyState(VK_DOWN) & 0x0001);
	bool keypressedRight = (GetAsyncKeyState(VK_RIGHT) & 0x0001);
	bool keypressedLeft = (GetAsyncKeyState(VK_LEFT) & 0x0001);
	bool keypressedSpace = (GetAsyncKeyState(VK_SPACE) & 0x0001);

// 제목의 빨간점기준 좌표
// TitleLocationPick(16,23)

	// 스페이스바를 클릭했을 때
	if (keypressedSpace)
	{
		SoundManager::getInstance().play(SOUND_EFFECT_BUTTON);

		// 빨간점이 GAME START 선택 좌표에 맞게 갔을경우, GAME START
		if (currentSelected == 0)
		{
			return CONTROL_MESSAGE_START_SETTING;
		}

		// 빨간점이 GAME Creator 선택 좌표에 맞게 갔을경우, GAME Creator
		if (currentSelected == 1)
		{
			return CONTROL_MESSAGE_START_CREATOR;
		}

		// 빨간점이 Good Bye... 선택 좌표에 맞게 갔을경우, 컷
		if (currentSelected == 2)
		{
			return CONTROL_MESSAGE_START_HOWTO;
		}

		// 빨간점이 Good Bye... 선택 좌표에 맞게 갔을경우, 컷
		if (currentSelected == 3)
		{
			return CONTROL_MESSAGE_QUIT;
		}
	}

	// Up키 입력 받기
	if (keypressedUp)
	{
		select(-1);
	}

	// Down키 입력 받기
	if (keypressedDown)
	{
		select(1);
	}

	return CONTROL_MESSAGE_CONTINUE;
}

// 매 프레임마다 update함수 실행 후 paint실행, MenuManager에서 그려야하는 object들을 화면에 그리는 함수
void MenuManager::paint()
{
	outputManager.init();
	outputManager.paintObject(title);

	for (int i = 0; i < messageList.size(); i++) {
		outputManager.paintObject(messageList[i]);
	}

	outputManager.paintScreen();
}