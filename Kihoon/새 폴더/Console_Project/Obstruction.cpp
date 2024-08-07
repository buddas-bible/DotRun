#include "Obstruction.h"
#include "vector2D.h"


Obstruction::Obstruction()
	: Object(0, 0), position2(0, 0)
	// , nVector(0, 0)
{

}

Obstruction::Obstruction(double x, double y, double x2, double y2)
	: Object(x, y), position2(x2, y2)
{

}

Obstruction::Obstruction(double x, double y, double x2, double y2, double normalX, double normalY)
	: Object(x, y), position2(x2, y2), 
	nVector(normalX, normalY)
{

}

Obstruction::~Obstruction()
{
	
}