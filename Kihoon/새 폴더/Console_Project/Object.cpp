#include "Object.h"
#include "vector2D.h"
#include <cmath>


Object::Object()
{
	position.X = 0;
	position.Y = 0;
}

/// xÁÂÇ¥, yÁÂÇ¥
Object::Object(double X, double Y)
{
	position.X = X;
	position.Y = Y;
}

Object::~Object()
{

}

