#include "Freefall.h"



Freefall::Freefall() : 
	ground(0.0, 90.0, 400.0, 90.0, 1, - 1), 
	wall_UP(0.0, 0.0, 400.0, 0.0, 1 , - 1),
	wall_A(230.0, 60.0, 400.0, 60.0, 1, - 1),
	wall_L(10.0, 0.0, 10.0, 100.0, - 1, 1),
	wall_R(390.0, 0.0, 390.0, 100.0, - 1, 1)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

}

Freefall::~Freefall()
{

}

void Freefall::init()
{

}

int Freefall::update(Ball& obj, long long deltaTime)
{

	// y�ӷ��� 0�̰� x�ӷ��� 0�� �ƴϸ� / ������ �����ٴ� ��
	if (obj.velocity.Y == 0 && obj.velocity.X != 0)
	{
		obj.setVelocityXY(0.5, 1);
	}

	/// x ��ǥ�� ���� x��ǥ + x�ӷ� * ���� �ð�
	obj.position.X = obj.position.X + (obj.velocity.X * (deltaTime / 1000.0));
	
	obj.velocity.Y = obj.velocity.Y + (GRAVITY * (deltaTime / 1000.0));
	

	/// Y��ǥ�� �ð����� Y �ӷ¸�ŭ ������ ��
	/// ������ Y �ӵ��� 0�̸� Y��ǥ�� �ٲ��� ����.
	obj.position.Y = obj.position.Y - (obj.velocity.Y * (deltaTime / 1000.0));


	collisioncheck.collisionCheck(obj, ground);
	collisioncheck.collisionCheck(obj, wall_UP);
	collisioncheck.collisionCheck(obj, wall_A);
	collisioncheck.collisionCheck(obj, wall_L);
	collisioncheck.collisionCheck(obj, wall_R);



	return RUN;
}

