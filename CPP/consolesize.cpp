#include <iostream>
#include <Windows.h>;

using namespace std;


void SetConsoleView()
{
	system("mode con:cols=160 lines=50");
	system("title Dot Run!!!. by Make The Run");
}

void DrawDino()
{

	printf(" $$$$$$$  \n");
	printf("$$$$$     \n");
	printf("$$$$$$$$$ \n");
	printf("$$$$$$    \n");
	printf("$$$$$$    \n");
	printf("$$$$$$    \n");
	printf("$$$$$     \n");
}


int main()
{
	SetConsoleView();
	DrawDino();
	DrawDino();
	DrawDino();
}