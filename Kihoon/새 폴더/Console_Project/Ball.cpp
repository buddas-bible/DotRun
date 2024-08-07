#include "Ball.h"
#include "vector2D.h"


Ball::Ball() 
	: Object(0, 0), 
	velocity(0),
	speed(0, 0),
	prePosition(0, 0)
{
	
}

Ball::Ball(double X, double Y, double velocity)
	: Object(X, Y), 
	velocity(velocity)
{

}

Ball::~Ball()
{

}

void Ball::init()
{

}

/// �ʱ� �ӷ��� ���� radian
void Ball::setVelocityXY(double theta)
{
	speed.X = velocity * cos(theta);
	speed.Y = velocity * sin(theta);
}

// �ӷ��� ������. ���� ����� ���� ����, �ӵ���
void Ball::setVelocityXY(double xCOR, double yCOR)
{
	speed.X = velocity * xCOR;
	speed.Y = velocity * yCOR;
}

/// ���� ��ǥ�� �����Ѵ�.
void Ball::savePrePosition(Ball& ball)
{
	ball.prePosition.X = ball.position.X;
	ball.prePosition.Y = ball.position.Y;
}