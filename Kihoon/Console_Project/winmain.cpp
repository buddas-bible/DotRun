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

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <SDKDDKVer.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"MyClassName";
	wc.lpszClassName = my_class_name;				//윈도우 클래스의 이름을 정의
	wc.lpfnWndProc = WndProc;						//윈도우의 메시지 처리 함수를 지정
	wc.cbClsExtra = NULL;							//예약 영역. 윈도우즈가 내부적으로 사용
	wc.cbWndExtra = NULL;							//예약 영역. 윈도우즈가 내부적으로 사용
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;		//윈도우의 배경 색상
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		//마우스 커서
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//아이콘
	wc.hInstance = hInstance;						//이 윈도우 클래스를 사용하는 프로그램의 번호
	wc.lpszMenuName = NULL;							//프로그램이 사용할 메뉴 //사용하지 않을 경우 이 멤버에 NULL을 대입
	wc.style = CS_HREDRAW | CS_VREDRAW;				//윈도우의 스타일을 정의

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(
		my_class_name,								//생성하고자 하는 윈도우의 클래스
		L"Test WinAPI",								//lpszWindowName 윈도우의 타이틀 바에 나타날 문자열
		WS_OVERLAPPEDWINDOW,						//dwStyle 만들고자 하는 윈도우의 형태
		100, 90, 400, 350,							//X, Y, nWidth, nHeight
		NULL,										//부모 윈도우가 있을 경우 부모 윈도우의 핸들
		NULL,										//생성 윈도우에서 사용할 메뉴의 핸들
		hInstance,									//프로그램의 핸들
		NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (true)		//메시지 큐에서 메시지를 읽어들인다 //MSG 구조체에 저장 //WM_QUIT일 경우 False
	{	
		if (PeekMessage(&msg, NULL, 0, 0, 0))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);				//키보드 입력 메시지를 가공. 문자가 입력되었다는 메시지(WM_CHAR)를 만드는 역할
			DispatchMessage(&msg);				//메시지를 프로그램의 메시지 처리 함수(WndProc)로 전달
		}
		else
		{




		}
	}
	return msg.wParam;
}