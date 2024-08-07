#include "vector3D.h"


vector3D::vector3D() : X(0), Y(0), Z(0)
{

}

vector3D::vector3D(double x, double y, double z) : X(x), Y(y), Z(z)
{

}

vector3D::~vector3D()
{

}

vector3D vector3D::cross(const vector3D& other) const
{
	return vector3D(
		Y * other.Z - Z * other.Y,
		Z * other.X - X * other.Z,
		X * other.Y - Y * other.X);
}

// º¤ÅÍ¿Í ½ºÄ®¶ó °ö¼À
vector3D vector3D::operator * (double n) const
{
	return vector3D(X * n, Y * n, Z * n);
}

// º¤ÅÍ µ¡¼À
vector3D vector3D::operator + (vector3D other) const
{
	return vector3D(X + other.X, Y + other.Y, Z + other.Z);
}

// º¤ÅÍ »¬¼À
vector3D vector3D::operator - (vector3D other) const
{
	return vector3D(X - other.X, Y - other.Y, Z - other.Z);
}

// °°ÀºÁö
bool vector3D::operator == (vector3D other) const
{
	return X == other.X && Y == other.Y && Z == other.Z;
}

// ºñ±³
bool vector3D::operator < (vector3D other) const
{
	return X < other.X && Y < other.Y && Z < other.Z;
}
