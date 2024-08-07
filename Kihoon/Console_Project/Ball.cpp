#include "Ball.h"
#include "vector2D.h"


Ball::Ball() 
	: Object(0, 0), 
	speed(0),
	velocity(0, 0),
	prePosition(0, 0)
{
	
}

Ball::Ball(double X, double Y, double speed)
	: Object(X, Y), 
	speed(speed)
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
	velocity.X = speed * cos(theta);
	velocity.Y = speed * sin(theta);
}

// �ӷ��� ������. ���� ����� ���� ����, �ӵ���
void Ball::setVelocityXY(double xCOR, double yCOR)
{
	velocity.X = speed * xCOR;
	velocity.Y = speed * yCOR;
}

/// ���� ��ǥ�� �����Ѵ�.
void Ball::savePrePosition(Ball& ball)
{
	ball.prePosition.X = ball.position.X;
	ball.prePosition.Y = ball.position.Y;
}