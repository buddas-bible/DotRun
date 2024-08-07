#include "collisionCheck.h"


CollisionCheck::CollisionCheck()
{

}

CollisionCheck::~CollisionCheck()
{

}

// �ݽð� ���, 
double CollisionCheck::ccw(vector2D vertexA, vector2D vertexB)
{
	return vertexA.cross(vertexB);
}

// A�� P�� �������� �� B�� �ݽð��ΰ�? �ð��ΰ�?
double CollisionCheck::ccw(vector2D vertexA, vector2D vertexB, vector2D vertexP)
{
	return ccw(vertexA - vertexP, vertexB - vertexP);
}


void CollisionCheck::collisionCheck(Ball& Object, Obstruction obstruction)
{
	// �浹�ϸ� ����
	// �浹 ���ϸ� ����

	double ball1 = ccw(Object.prePosition, Object.position, obstruction.position);
	double ball2 = ccw(Object.prePosition, Object.position, obstruction.position2);

	double wall1 = ccw(obstruction.position, obstruction.position2, Object.position);
	double wall2 = ccw(obstruction.position, obstruction.position2, Object.prePosition);

	if (ball1 * ball2 == 0 &&
		wall1 * wall2 == 0)
	{
		return;
	}
	else if (ball1 * ball2 < 0 &&
		wall1 * wall2 < 0)
	{
		IntersectPoint(Object, obstruction);
	}
	else if (ball1 * ball2 == 0 &&
		wall1 * wall2 < 0)
	{
		IntersectPoint(Object, obstruction);
	}
	else if (ball1 * ball2 < 0 &&
		wall1 * wall2 == 0)
	{
		IntersectPoint(Object, obstruction);
	}
	else
	{
		return;
	}
}



/// <summary>
/// ������ ã�� �Լ�
/// </summary>
/// <param name="_objectA">�����̴� ������Ʈ</param>
/// <param name="_objectB">���ع�</param>
void CollisionCheck::IntersectPoint(Ball& Object, Obstruction obstruction)
{
	// (x1 - x2)(y3 - y4) - (y1 - y2)(x3 - x4)
	double under = (Object.position.X - Object.prePosition.X) * (obstruction.position.Y - obstruction.position2.Y)
		- (Object.position.Y - Object.prePosition.Y) * (obstruction.position.X - obstruction.position2.X);

	// (x_1y_2-y_1x_2)(x_3-x_4)-(x_1-x_2)(x_3y_4-y_3x_4)
	double x = (((Object.position.X * Object.prePosition.Y) - (Object.position.Y * Object.prePosition.X)) * (obstruction.position.X - obstruction.position2.X))
		- ((Object.position.X - Object.prePosition.X) * ((obstruction.position.X * obstruction.position2.Y) - (obstruction.position.Y * obstruction.position2.X)));

	// (x_1y_2-y_1x_2)(y_3-y_4)-(y_1-y_2)(x_3y_4-y_3x_4)
	double y = (((Object.position.X * Object.prePosition.Y) - (Object.position.Y * Object.prePosition.X)) * (obstruction.position.Y - obstruction.position2.Y))
		- ((Object.position.Y - Object.prePosition.Y) * ((obstruction.position.X * obstruction.position2.Y) - (obstruction.position.Y * obstruction.position2.X)));

	x = x / under;
	y = y / under;

	if (obstruction.nVector.X == - 1)
	{
		if (Object.prePosition.X <= x)
		{
			Object.position.X = x - abs(Object.position.X - x);
			// Object.position.X = obstruction.position.X - EPSILON;
		}
		else
		{
			Object.position.X = x + abs(Object.position.X - x);
			// Object.position.X = obstruction.position.X + EPSILON;
		}
	}
	else if (obstruction.nVector.Y == - 1)
	{
		if (Object.prePosition.Y <= y)
		{
			Object.position.Y = y - abs(Object.position.Y - y);
		}
		else
		{
			Object.position.Y = y + abs(Object.position.Y - y);
		}
	}

	Object.velocity.X = Object.velocity.X * obstruction.nVector.X * 0.8;
	Object.velocity.Y = Object.velocity.Y * obstruction.nVector.Y * 0.8;
}