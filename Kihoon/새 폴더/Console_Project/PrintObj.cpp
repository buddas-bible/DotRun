#include "vector2D.h"
#include "PrintObj.h"


PrintManager::PrintManager()
{

}

PrintManager::~PrintManager()
{

}

void PrintManager::swap(double& a, double& b)
{
	double temp;
	temp = a;
	a = b;
	b = temp;
}

void PrintManager::gotoxy(int x, int y, char ch)
{
	COORD pos = { x , y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	std::cout << ch;
}

void PrintManager::printObj(Obstruction obstruction)
{
	double temp;
	if (obstruction.position.X < obstruction.position2.X)
	{
		swap(obstruction.position.X, obstruction.position2.X);
	}
	if (obstruction.position.Y < obstruction.position2.Y)
	{
		swap(obstruction.position.Y, obstruction.position2.Y);
	}

	// ������ �����Ŀ� x��ǥ�� �־ y���� ã�� �ݿø�
	for (double i = round(obstruction.position2.X + 0.005); i <= obstruction.position.X; i++)
	{
		double j = 0;
		j = round(((obstruction.position2.Y - obstruction.position.Y) / (obstruction.position2.X - obstruction.position.X) * (i - obstruction.position2.X) + obstruction.position2.Y) + 0.005);
		gotoxy(i, j, '*');
	}
	// ���� ���Լ��� y��ǥ�� �־ x���� ã�� �ݿø�
	for (double j = round(obstruction.position2.Y + 0.005); j <= obstruction.position.Y; j++)
	{
		double i = 0;
		i = round(((obstruction.position2.X - obstruction.position.X) / (obstruction.position2.Y - obstruction.position.Y) * (i - obstruction.position2.Y) + obstruction.position2.X) + 0.005);
		gotoxy(i, j, '*');
	}
}