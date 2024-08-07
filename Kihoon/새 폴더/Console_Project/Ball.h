#pragma once
#include "cmath"
#include "Object.h"
#include "vector2D.h"

class vector2D;

class Ball : public Object
{
private:

public:
	Ball();
	Ball(double, double, double);
	~Ball();
	vector2D prePosition;
	vector2D speed;

	double velocity;

	void init();

	void setVelocityXY(double);
	void setVelocityXY(double, double);

	void savePrePosition(Ball&);

protected:

};