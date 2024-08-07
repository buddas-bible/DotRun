#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "CreatorManager.h"
#include "DotRunDef.h"
#include "OutputManager.h"
#include "DataManager.h"

void gotoxy(int x, int y, const char* s)
{
	COORD Pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	printf("%s", s);
}

// 스네이크 움직임 구현
// GetAsyncKeyState를 사용하지 않은 이유
// 대각선 입력과 같은 두개 이상의 입력이 필요없어, 하나의 키만 받아도 충분한 _getch 사용
void CreatorManager::move_snake(POS* snake, int len)
{
	static int dir = -1;
	// 키보드 입력버퍼만 확인하여 true, false 값을 리턴
	if (_kbhit())
	{
		int key = _getch();
		bool is224 = true;
		while (key != 224) {
			if (!_kbhit()) {
				is224 = false;
				break;
			}
			key = _getch();
		}

		if (is224) {
			key = _getch();
			switch (key)
			{
				// UP키
				case 72:
				{
					dir = 0;
					break;
				}
				//DOWN키
				case 80:
				{
					dir = 1;
					break;
				}
				//LEFT키
				case 75:
				{
					dir = 2;
					break;
				}
				//RIGHT키
				case 77:
				{
					dir = 3;
					break;
				}
			}
		}
	}
	if (dir != -1)
	{
		footprint = snake[len - 1];
		for (int i = len - 1; i > 0; i--)
		{
			snake[i] = snake[i - 1];
		}
	}
	switch (dir)
	{
		// UP
		case 0:
		{
			snake[0].y--;
			break;
		}
		// DOWN
		case 1:
		{
			snake[0].y++;
			break;
		}
		// LEFT
		case 2:
		{
			snake[0].x--;
			break;
		}
		// RIGHT
		case 3:
		{
			snake[0].x++;
			break;
		}
	}
	
}

// 스네이크가 충돌했는지 확인
// snake[0] = 머리, snake[i] = 몸통 부터 꼬리 까지
int check_snake(POS* snake, int len)
{
	// 빈 곳
	if (snake[0].x == 40 && snake[0].y == 29)
	{
		return 1;
	}

	if (snake[0].x == 0 || snake[0].y == 0)
	{
		return 0;
	}

	if ((snake[0].x == 40 && snake[0].y < 30) || (snake[0].x < 40 && snake[0].y == 30)) {
		return 0;
	}

	if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == 80 || snake[0].y == 50)
	{
		return 0;
	}

	for (int i = 1; i < len; i++)
	{
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
		{
			return 0;
		}
	}
	return 1;
}

CreatorManager::CreatorManager(OutputManager& out, DataManager& data) :
	outputManager(out), dataManager(data)
{

}

void CreatorManager::init()
{
	dir = -1;
	len = 2;
	score = 0;
	timecheck = 0;
	gameQuit = false;

	// item을 랜덤으로 배치하기위해 시간함수를 사용해서 랜덤함수 생성
	srand(time(NULL));

	for (int i = 0; i < len; i++)
	{
		// 시작 위치
		snake[i].x = 15 + i;
		snake[i].y = 10;
	}

	// 아이템 랜덤 생성
	item.x = rand() % 38 + 1;
	item.y = rand() % 28 + 1;

	messageList.clear();
	messageList.push_back(MessageObject("- Make The Run -", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 100, 5, 40, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("KIM BEOM JOON", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 100, 8, 40, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("JUNG KI HOON", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 100, 11, 40, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("NA DONG HOON", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 100, 14, 40, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_BG_WHITE, COLOR_BG_WHITE, 100, 26, 40, 1, LAYER_MESSAGEBOX + 1));
	messageList.push_back(MessageObject("", ALIGNMENT_CENTER, COLOR_FONT_BLACK, COLOR_BG_WHITE, COLOR_BG_WHITE, 100, 32, 40, 1, LAYER_MESSAGEBOX + 1));
	messageList.push_back(MessageObject("and YOU", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 100, 26, 40, 1, LAYER_MESSAGEBOX));
	messageList.push_back(MessageObject("Thank you", ALIGNMENT_CENTER, COLOR_FONT_WHITE, COLOR_BG_BLACK, COLOR_BG_BLACK, 100, 32, 40, 1, LAYER_MESSAGEBOX));

	for (int i = 0; i < messageList.size(); i++) {
		messageList[i].setVisible(false);
	}

	int key;
	do
	{
		key = _getch();
	} while (_kbhit());
}

int CreatorManager::update(long long deltaTime)
{
	timecheck += deltaTime;

	if (timecheck > period) {
		timecheck -= period;

		if (check_snake(snake, len) == 0)
		{
			snakegameover();
		}

		// 아이템을 먹었을 경우
		if (snake[0].x == item.x && snake[0].y == item.y)
		{
			score += 10;

			// 아이템 랜덤 재 생성
			item.x = rand() % 38 + 1;
			item.y = rand() % 28 + 1;

			if (len < 100)
			{
				snake[len] = snake[len - 1];
				len++;
			}

			// 화면 띄우기
			if (score == scoreShowTeam) {
				messageList[0].setVisible(true);
			}
			if (score == scoreShowName0) {
				messageList[1].setVisible(true);
			}
			if (score == scoreShowName1) {
				messageList[2].setVisible(true);
			}
			if (score == scoreShowName2) {
				messageList[3].setVisible(true);
			}
			if (score == scoreShowSpecial) {
				messageList[4].setVisible(true);
				messageList[5].setVisible(true);
				messageList[6].setVisible(true);
				messageList[7].setVisible(true);
				item.x = 42;
				item.y = 29;
			}
		}

		move_snake(snake, len);
	}

	if (snake[0].x == 40 && snake[0].y == 29) {
		messageList[4].setVisible(false);
		messageList[5].setVisible(false);
	}

	if (gameQuit) {
		return CONTROL_MESSAGE_START_MENU;
	}

	return CONTROL_MESSAGE_CONTINUE;
}

void CreatorManager::snakegameover()
{
	gameQuit = true;
}

void CreatorManager::paint()
{
	outputManager.init();

	for (int i = 0; i < messageList.size(); i++) {
		outputManager.paintObject(messageList[i]);
	}

	outputManager.paintScreen();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_FONT_WHITE);

	// 아이템 표시
	gotoxy(item.x, item.y, "★");

	// snake
	if (footprint.x != -1 && footprint.y != -1) {
		gotoxy(footprint.x, footprint.y, "  ");
		footprint.x = -1;
		footprint.y = -1;
	}
	gotoxy(snake[0].x, snake[0].y, "●");
	for (int i = 1; i < len; i++) {
		gotoxy(snake[i].x, snake[i].y, "○");
	}

	// 점수 표시
	gotoxy(1, 32, "Score : ");
	printf("%d", score);

	gotoxy(0, 0, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	for (int i = 1; i < 30; i++)
	{
		gotoxy(0, i, "■");
		gotoxy(40, i, "■");
	}
	gotoxy(0, 30, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

	if (gameQuit) {
		system("cls");
	}
}