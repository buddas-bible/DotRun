// 123.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "123.h"

#define MAX_LOADSTRING 100

// 전역 변수:


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPWSTR    lpCmdLine,
                     int       nCmdShow)
{
	WNDCLASS wcex;
    MSG msg;

	wchar_t my_class_name[] = L"MyClassName";
    wcex.lpszClassName = my_class_name;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_MY123));
	wcex.hInstance = hInstance;
	wcex.lpszMenuName = NULL;
	wcex.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wcex);

	HWND hWnd = CreateWindow(
		my_class_name,								//생성하고자 하는 윈도우의 클래스
		L"Test WinAPI",								//lpszWindowName 윈도우의 타이틀 바에 나타날 문자열
		WS_OVERLAPPEDWINDOW,						//dwStyle 만들고자 하는 윈도우의 형태
		10, 10, 1610, 910,							//X, Y, nWidth, nHeight
		NULL,										//부모 윈도우가 있을 경우 부모 윈도우의 핸들
		NULL,										//생성 윈도우에서 사용할 메뉴의 핸들
		hInstance,									//프로그램의 핸들
		NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

    HDC hdc = GetDC(hWnd);

    // 기본 메시지 루프입니다:
    while (TRUE)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
		    if (msg.message == WM_QUIT) break;
            DispatchMessage(&msg);
        }
        else
        {
            Rectangle(hdc, 10, 10, 300, 300);
            Rectangle(hdc, 310, 310, 610, 610);
        }
    }
    ReleaseDC(hWnd, hdc);

    return (int) msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}