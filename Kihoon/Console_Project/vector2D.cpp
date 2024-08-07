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

// 외적
// 벡터 외적은 3차원이 기본이지만
// 2차원에서의 외적은 x, y가 0이므로 z값만 남음
// 이 값의 부호로 방향을 알 수 있다. 
double vector2D::cross(const vector2D& other) const
{
	return X * other.Y - Y * other.X;
}

double vector2D::dot(const vector2D& other) const
{
	return X * other.X + Y * other.Y;
}

// 벡터와 스칼라 곱셈
vector2D vector2D::operator * (double n) const
{
	return vector2D(X * n, Y * n);
}

// 벡터 덧셈
vector2D vector2D::operator + (vector2D other) const
{
	return vector2D(X + other.X, Y + other.Y);
}

// 벡터 뺄셈
vector2D vector2D::operator - (vector2D other) const
{
	return vector2D(X - other.X, Y - other.Y);
}

// 같은지
bool vector2D::operator == (vector2D other) const
{
	return X == other.X && Y == other.Y;
}

// 비교
bool vector2D::operator < (vector2D other) const
{
	return X < other.X&& Y < other.Y;
}
