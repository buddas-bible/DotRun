#include <iostream>
#include <ctime>
#include <Windows.h>
#include <string>
#include <thread>
#include "DotRunDef.h"
#include "MenuManager.h"
#include "GameManager.h"
#include "SettingManager.h"
#include "OutputManager.h"
#include "ResultManager.h"
#include "HowtoManager.h"
#include "DataManager.h"
#include "CreatorManager.h"
using namespace std;


int main()
{
	// 시간으로 시드값 설정
	srand((unsigned int)time(NULL));

	ios_base::sync_with_stdio(false);
	cout.tie();

	// 실행 중 콘솔사이즈 변경 불가능하도록 설정
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	
	// 콘솔사이즈 160x50
	system("mode con: cols=160 lines=50 | title Dot Run!!");
	
	
	// Manager 클래스들의 객체 생성
	OutputManager outputManager;
	outputManager.init();

	DataManager dataManager;
	dataManager.init();

	MenuManager menuManager = MenuManager(outputManager, dataManager);
	GameManager gameManager = GameManager(outputManager, dataManager);
	SettingManager settingManager = SettingManager(outputManager, dataManager);
	ResultManager resultManager = ResultManager(outputManager, dataManager);
	HowToManager howtoManager = HowToManager(outputManager, dataManager);
	CreatorManager creatorManager = CreatorManager(outputManager, dataManager);

	int state = STATE_MENU;

	// 초기화
	switch (state)
	{
	case STATE_MENU:
		menuManager.init();
		break;
		
	case STATE_GAME:
		gameManager.init();
		break;

	case STATE_SETTING:
		settingManager.init();
		break;

	case STATE_RESULT:
		resultManager.init();
		break;

	case STATE_HOWTO:
		howtoManager.init();
		break;

	case STATE_CREATOR:
		creatorManager.init();
		break;
	}

	time_t lastframe = clock();

	while (state != STATE_QUIT)
	{
		// 아무일이 없으면 while문 계속 돌린다.
		int response = CONTROL_MESSAGE_CONTINUE;

		// deltaTime 계산, Manager 동작 전 시간 체크
		time_t deltaTime = clock() - lastframe;
		lastframe = clock();

		// Manager 동작
		switch (state)
		{
			case STATE_MENU:
				response = menuManager.update(deltaTime);
				menuManager.paint();
				break;

			case STATE_GAME:
				response = gameManager.update(deltaTime);
				gameManager.paint();
				break;
			case STATE_SETTING:
				response = settingManager.update(deltaTime);
				settingManager.paint();
				break;
			
			case STATE_RESULT:
				response = resultManager.update(deltaTime);
				resultManager.paint();
				break;

			case STATE_HOWTO:
				response = howtoManager.update(deltaTime);
				howtoManager.paint();
				break;

			case STATE_CREATOR:
				response = creatorManager.update(deltaTime);
				creatorManager.paint();
				break;
		}

		// update 결과에 따른 동작
		switch (response)
		{
				// 메뉴에서 나가게
			case CONTROL_MESSAGE_QUIT:
				state = STATE_QUIT;
				break;

				// 메뉴에서 게임으로 가는 경우
			case CONTROL_MESSAGE_START_GAME:
				state = STATE_GAME;
				gameManager.init();
				break;

				// 게임에서 메뉴로 돌아가는 경우
			case CONTROL_MESSAGE_START_MENU:
				state = STATE_MENU;
				menuManager.init();
				break;
				
			case CONTROL_MESSAGE_START_SETTING:
				state = STATE_SETTING;
				settingManager.init();
				break;

			case CONTROL_MESSAGE_START_RESULT:
				state = STATE_RESULT;
				resultManager.init();
				break;

			case CONTROL_MESSAGE_START_HOWTO:
				state = STATE_HOWTO;
				howtoManager.init();
				break;

			case CONTROL_MESSAGE_START_CREATOR:
				state = STATE_CREATOR;
				creatorManager.init();
				break;
		}

		long long xxxx = (clock() - lastframe);
		this_thread::sleep_for(std::chrono::milliseconds((1000 / 120) - (clock() - lastframe)));
	}

	return 0;
}