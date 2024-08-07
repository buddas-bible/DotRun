#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "windows.h"
#include "text_define.h"

#include "PrintObj.h"
#include "collisionCheck.h"

#include "Ball.h"
#include "Obstruction.h"



class vector2D;

class Freefall
{
private:
	// 반발계수
	// float COR = -0.8f;

public:
	Freefall();
	~Freefall();
	
	void init();
	int update(Ball&, long long);

	Obstruction ground;
	Obstruction wall_L;
	Obstruction wall_R;
	Obstruction wall_A;
	Obstruction wall_UP;

	CollisionCheck collisioncheck;
};