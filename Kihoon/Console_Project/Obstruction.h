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
	/// ¹æÇØ¹°
	/// </summary>
	/// <param name="">ÇÑ Á¡ÀÇ X ÁÂÇ¥</param>
	/// <param name="">ÇÑ Á¡ÀÇ Y ÁÂÇ¥</param>
	/// <param name="">ÇÑ Á¡ÀÇ X2 ÁÂÇ¥</param>
	/// <param name="">ÇÑ Á¡ÀÇ Y2 ÁÂÇ¥</param>
	/// <param name="">Æ¨±æ ¹æÇâ X -1, 0, 1·Î ±âÀÔÇÒ °Í</param>
	/// <param name="">Æ¨±æ ¹æÇâ Y -1, 0, 1·Î ±âÀÔÇÒ °Í</param>
	Obstruction(double, double, double, double, double, double);
	~Obstruction();

	vector2D position2;
	vector2D nVector;
};