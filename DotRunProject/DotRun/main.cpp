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
	// �ð����� �õ尪 ����
	srand((unsigned int)time(NULL));

	ios_base::sync_with_stdio(false);
	cout.tie();

	// ���� �� �ֻܼ����� ���� �Ұ����ϵ��� ����
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	
	// �ֻܼ����� 160x50
	system("mode con: cols=160 lines=50 | title Dot Run!!");
	
	
	// Manager Ŭ�������� ��ü ����
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

	// �ʱ�ȭ
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
		// �ƹ����� ������ while�� ��� ������.
		int response = CONTROL_MESSAGE_CONTINUE;

		// deltaTime ���, Manager ���� �� �ð� üũ
		time_t deltaTime = clock() - lastframe;
		lastframe = clock();

		// Manager ����
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

		// update ����� ���� ����
		switch (response)
		{
				// �޴����� ������
			case CONTROL_MESSAGE_QUIT:
				state = STATE_QUIT;
				break;

				// �޴����� �������� ���� ���
			case CONTROL_MESSAGE_START_GAME:
				state = STATE_GAME;
				gameManager.init();
				break;

				// ���ӿ��� �޴��� ���ư��� ���
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