#pragma once
#include <vector>
#include "Object.h"

class vector2D;

class Obstruction : public Object
{
public:
	Obstruction();
	Obstruction(double, double, double, double);

	/// <summary>
	/// 방해물
	/// </summary>
	/// <param name="">한 점의 X 좌표</param>
	/// <param name="">한 점의 Y 좌표</param>
	/// <param name="">한 점의 X2 좌표</param>
	/// <param name="">한 점의 Y2 좌표</param>
	/// <param name="">튕길 방향 X -1, 0, 1로 기입할 것</param>
	/// <param name="">튕길 방향 Y -1, 0, 1로 기입할 것</param>
	Obstruction(double, double, double, double, double, double);
	~Obstruction();

	vector2D position2;
	vector2D nVector;
};