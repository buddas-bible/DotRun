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

	// y속력이 0이고 x속력이 0이 아니면 / 땅에서 굴러다닐 때
	if (obj.speed.Y == 0 && obj.speed.X != 0)
	{
		obj.setVelocityXY(0.5, 1);
	}

	/// x 좌표는 이전 x좌표 + x속력 * 단위 시간
	obj.position.X = obj.position.X + (obj.speed.X * (deltaTime / 1000.0));
	
	obj.speed.Y = obj.speed.Y + (GRAVITY * (deltaTime / 1000.0));
	

	/// Y좌표에 시간마다 Y 속력만큼 영향을 줌
	/// 어차피 Y 속도가 0이면 Y좌표가 바뀌지 않음.
	obj.position.Y = obj.position.Y - (obj.speed.Y * (deltaTime / 1000.0));


	collisioncheck.collisionCheck(obj, ground);
	collisioncheck.collisionCheck(obj, wall_UP);
	collisioncheck.collisionCheck(obj, wall_A);
	collisioncheck.collisionCheck(obj, wall_L);
	collisioncheck.collisionCheck(obj, wall_R);



	return RUN;
}

/*
	// 0.005자리부터 반올림

	floor(obj.velocityX + 0.005);
	floor(obj.velocityY + 0.005);

	// 벽에 부딪치는가?
	if (obj.collisionCheck(obj, wall_L))
	{
		obj.IntersectPoint(obj, wall_L)
		obj.X = wall_L.X + abs(obj.X - wall_L.X);
		//obj.X = wall_L.X + 1;
		obj.velocityX = obj.velocityX * COR;
	}

	if (obj.collisionCheck(obj, wall_R))
	{
		obj.X = wall_R.X - abs(obj.X - wall_R.X);
		//obj.X = wall_R.X - 1;
		obj.velocityX = obj.velocityX * COR;
	}

	if (obj.collisionCheck(obj, wall_1))
	{
		if (obj.preY < wall_1.Y)
		{
			obj.Y = wall_1.Y - abs(obj.Y - wall_1.Y);
			//obj.Y = wall_1.Y - 1;
		}
		else
		{
			obj.Y = wall_1.Y + abs(obj.Y - wall_1.Y);
			//obj.Y = wall_1.Y + 1;
		}

		obj.velocityY = obj.velocityY * COR;
	}

	if (obj.collisionCheck(obj, wall_UP))
	{
		obj.Y = wall_UP.Y + abs(obj.Y - wall_UP.Y);
		//obj.Y = wall_UP.Y + 1;
		obj.velocityY = obj.velocityY * COR;
	}

	// Y좌표가 GROUND를 넘으면 Y좌표를 GROUND로 옮기고 운동을 이어서 함.
	if (obj.collisionCheck(obj, ground))
	{
		obj.Y = ground.Y - abs(obj.Y - ground.Y);
		//obj.Y = ground.Y - 1;
		obj.velocityY = obj.velocityY * COR;

		if (obj.velocityY < 1 && obj.velocityY > -1)
		{
			obj.Y = ground.Y - 1;
			obj.velocityY = 0;
			obj.velocityX = obj.velocityX * - COR;
		}
	}
*/