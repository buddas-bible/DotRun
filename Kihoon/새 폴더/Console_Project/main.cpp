#include <iostream>
#include <vector>
#include <ctime>
#include <thread>
#include <windows.h>

#include "PrintObj.h"

#include "Freefall.h"
#include "collisionCheck.h"

#include "Object.h"
#include "Ball.h"
#include "Obstruction.h"


/// <summary>
/// 콘솔 창에서의 좌표는 일반 좌표계랑은 다르다.
/// X는 오른쪽이 증가
/// Y는 아래가 증가
/// 
/// 만약 콘솔 창에서 물체가 떨어지는 듯한 느낌을 주고 싶다면 Y값을 증가 시켜야 함
/// 가속도도 +쪽으로 해야함
/// </summary>
/// <returns>0</returns>
int main()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	system("mode con: cols=400 lines=100 | title Su!!");

	Freefall freefall;
	freefall.init();

	Ball object(50.0, 70.0, 80.0);
	object.setVelocityXY(PI / 7);

	PrintManager printManager;

	CollisionCheck collisioncheck;

	time_t lastframe = clock();
	object.savePrePosition(object);

	int state = RUN;
	while (state != EXIT)
	{
		// system("cls");
		time_t deltaTime = clock() - lastframe;
		lastframe = clock();
		
		object.savePrePosition(object);

		switch (state)
		{
		case RUN:
		{
			printManager.gotoxy(object.position.X, object.position.Y, ' ');
			freefall.update(object, deltaTime);
			printManager.gotoxy(object.position.X, object.position.Y, '@');

			printManager.printObj(freefall.wall_L);
			printManager.printObj(freefall.wall_R);
			printManager.printObj(freefall.wall_A);
			printManager.printObj(freefall.wall_UP);
			printManager.printObj(freefall.ground);

		}

		default:
			break; 
		}
		long long xxxx = (clock() - lastframe);
		std::this_thread::sleep_for(std::chrono::milliseconds((1000 / 120) - (clock() - lastframe)));
	}
	return 0;
}