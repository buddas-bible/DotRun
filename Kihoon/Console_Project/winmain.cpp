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
	wc.lpszClassName = my_class_name;				//������ Ŭ������ �̸��� ����
	wc.lpfnWndProc = WndProc;						//�������� �޽��� ó�� �Լ��� ����
	wc.cbClsExtra = NULL;							//���� ����. ������� ���������� ���
	wc.cbWndExtra = NULL;							//���� ����. ������� ���������� ���
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;		//�������� ��� ����
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);		//���콺 Ŀ��
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//������
	wc.hInstance = hInstance;						//�� ������ Ŭ������ ����ϴ� ���α׷��� ��ȣ
	wc.lpszMenuName = NULL;							//���α׷��� ����� �޴� //������� ���� ��� �� ����� NULL�� ����
	wc.style = CS_HREDRAW | CS_VREDRAW;				//�������� ��Ÿ���� ����

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(
		my_class_name,								//�����ϰ��� �ϴ� �������� Ŭ����
		L"Test WinAPI",								//lpszWindowName �������� Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�
		WS_OVERLAPPEDWINDOW,						//dwStyle ������� �ϴ� �������� ����
		100, 90, 400, 350,							//X, Y, nWidth, nHeight
		NULL,										//�θ� �����찡 ���� ��� �θ� �������� �ڵ�
		NULL,										//���� �����쿡�� ����� �޴��� �ڵ�
		hInstance,									//���α׷��� �ڵ�
		NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (true)		//�޽��� ť���� �޽����� �о���δ� //MSG ����ü�� ���� //WM_QUIT�� ��� False
	{	
		if (PeekMessage(&msg, NULL, 0, 0, 0))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);				//Ű���� �Է� �޽����� ����. ���ڰ� �ԷµǾ��ٴ� �޽���(WM_CHAR)�� ����� ����
			DispatchMessage(&msg);				//�޽����� ���α׷��� �޽��� ó�� �Լ�(WndProc)�� ����
		}
		else
		{




		}
	}
	return msg.wParam;
}