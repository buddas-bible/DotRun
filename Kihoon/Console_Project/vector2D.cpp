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

// ����
// ���� ������ 3������ �⺻������
// 2���������� ������ x, y�� 0�̹Ƿ� z���� ����
// �� ���� ��ȣ�� ������ �� �� �ִ�. 
double vector2D::cross(const vector2D& other) const
{
	return X * other.Y - Y * other.X;
}

double vector2D::dot(const vector2D& other) const
{
	return X * other.X + Y * other.Y;
}

// ���Ϳ� ��Į�� ����
vector2D vector2D::operator * (double n) const
{
	return vector2D(X * n, Y * n);
}

// ���� ����
vector2D vector2D::operator + (vector2D other) const
{
	return vector2D(X + other.X, Y + other.Y);
}

// ���� ����
vector2D vector2D::operator - (vector2D other) const
{
	return vector2D(X - other.X, Y - other.Y);
}

// ������
bool vector2D::operator == (vector2D other) const
{
	return X == other.X && Y == other.Y;
}

// ��
bool vector2D::operator < (vector2D other) const
{
	return X < other.X&& Y < other.Y;
}
