#include "collisionCheck.h"


CollisionCheck::CollisionCheck()
{

}

CollisionCheck::~CollisionCheck()
{

}

// 반시계 양수, 
double CollisionCheck::ccw(vector2D vertexA, vector2D vertexB)
{
	return vertexA.cross(vertexB);
}

// A가 P를 기준으로 본 B는 반시계인가? 시계인가?
double CollisionCheck::ccw(vector2D vertexA, vector2D vertexB, vector2D vertexP)
{
	return ccw(vertexA - vertexP, vertexB - vertexP);
}

/*
bool CollisionCheck::ParalleSegments(vector2D vertexA, vector2D vertexB, vector2D vertexC, vector2D vertexD, vector2D& vertexP)
{
	if (ccw(vertexA, vertexB, vertexC) != 0 || vertexB < vertexC || vertexD < vertexA)
	{
		return false;
	}

	if (vertexA < vertexC)
	{
		vertexP = vertexC;
	}

	else
	{
		vertexP = vertexA;
	}
	return true;
}

// ab를 지나는 직선과, cd를 지나는 직선의 교점을 x에 반환함.
bool CollisionCheck::LineIntersection(vector2D vertexA, vector2D vertexB, vector2D vertexC, vector2D vertexD, vector2D& vertexP)
{
	double det = (vertexB - vertexA).cross(vertexD - vertexC);

	if (fabs(det) < EPSILON)
	{
		return false;
	}

	vertexP = vertexA + (vertexB - vertexA) * ((vertexC - vertexA).cross(vertexD - vertexC) / det);
	return true;
}
*/

///// object와 obstruction의 pre 방향 비교
//int Object::CCW1(Object object, Object obstruction)
//{
//	// (x2-x1)(y3-y1)-(x3-x1)(y2-y1)
//	// x1y2 + x2y3 + x3y1 - (x2y1 + x3y2 + x1y3) 
//	int op = (object.X - object.X) * (obstruction.Y - object.Y)
//		- (obstruction.X - object.X) * (object.Y - object.Y);
//
//	// 반시계
//	if (op > 0)
//	{
//		return 1;
//	}
//
//	// 겹침
//	else if (op == 0)
//	{
//		return 0;
//	}
//
//	// 시계
//	else
//	{
//		return - 1;
//	}
//}
//
///// object와 obstruction의 position 방향 비교
//int Object::CCW2(Object object, Object obstruction)
//{
//	// (x2-x1)(y3-y1)-(x3-x1)(y2-y1)
//	// (이전x - x)(y3 - y) - (x3 - x)(이전y - y)
//	int op = (object.X - object.X) * (obstruction.Y - object.Y)
//		- (obstruction.X - object.X) * (object.Y - object.Y);
//
//	// 반시계
//	if (op > 0)
//	{
//		return 1;
//	}
//
//	// 겹침
//	else if (op == 0)
//	{
//		return 0;
//	}
//
//	// 시계
//	else
//	{
//		return -1;
//	}
//}


void CollisionCheck::collisionCheck(Ball& Object, Obstruction obstruction)
{
	// 충돌하면 실행
	// 충돌 안하면 안함

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
/// 교차점 찾는 함수
/// </summary>
/// <param name="_objectA">움직이는 오브젝트</param>
/// <param name="_objectB">방해물</param>
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
	/*
	*/


	

	if (obstruction.nVector.X == - 1)
	{
		if (Object.prePosition.X <= x)
		//if (Object.prePosition.X <= obstruction.position.X)
		{
			// Object.position.X = x - abs(Object.position.X - x);
			Object.position.X = obstruction.position.X - EPSILON;
		}
		else
		{
			// Object.position.X = x + abs(Object.position.X - x);
			Object.position.X = obstruction.position.X + EPSILON;
		}
	}
	else if (obstruction.nVector.Y == - 1)
	{
		if (Object.prePosition.Y <= y)
		//if (Object.prePosition.Y <= obstruction.position.Y)
		{
			Object.position.Y = y - abs(Object.position.Y - y);
			//Object.position.Y = obstruction.position.Y - EPSILON;
		}
		else
		{
			Object.position.Y = y + abs(Object.position.Y - y);
			//Object.position.Y = obstruction.position.Y + EPSILON;
		}
	}

	
	Object.speed.X = Object.speed.X * obstruction.nVector.X * 0.8;
	Object.speed.Y = Object.speed.Y * obstruction.nVector.Y * 0.8;


	
}