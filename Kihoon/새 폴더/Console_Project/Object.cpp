#include "Object.h"
#include "vector2D.h"
#include <cmath>


Object::Object()
{
	position.X = 0;
	position.Y = 0;
}

/// x��ǥ, y��ǥ
Object::Object(double X, double Y)
{
	position.X = X;
	position.Y = Y;
}

Object::~Object()
{

}

