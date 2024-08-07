#pragma once
#include "Ball.h"
#include "Obstruction.h"

class vector2D;
class Object;

class CollisionCheck
{
private:

public:
	CollisionCheck();
	~CollisionCheck();
	double ccw(vector2D, vector2D);
	double ccw(vector2D, vector2D, vector2D);

	void collisionCheck(Ball&, Obstruction);
	void IntersectPoint(Ball&, Obstruction);

protected:

};