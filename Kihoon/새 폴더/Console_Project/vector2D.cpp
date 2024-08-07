#include "vector2D.h"


vector2D::vector2D()
{

}

vector2D::vector2D(double x, double y) : X(x), Y(y)
{

}

vector2D::~vector2D()
{

}

// ¿ÜÀû
double vector2D::cross(const vector2D& other) const
{
	return X * other.Y - Y * other.X;
}

// º¤ÅÍ °ö¼À
vector2D vector2D::operator * (double n) const
{
	return vector2D(X * n, Y * n);
}

// º¤ÅÍ µ¡¼À
vector2D vector2D::operator + (vector2D other) const
{
	return vector2D(X + other.X, Y + other.Y);
}

// º¤ÅÍ »¬¼À
vector2D vector2D::operator - (vector2D other) const
{
	return vector2D(X - other.X, Y - other.Y);
}

// °°ÀºÁö
bool vector2D::operator == (vector2D other) const
{
	return X == other.X && Y == other.Y;
}

// ºñ±³
bool vector2D::operator < (vector2D other) const
{
	return X < other.X&& Y < other.Y;
}
