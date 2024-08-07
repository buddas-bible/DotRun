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
	/// ���ع�
	/// </summary>
	/// <param name="">�� ���� X ��ǥ</param>
	/// <param name="">�� ���� Y ��ǥ</param>
	/// <param name="">�� ���� X2 ��ǥ</param>
	/// <param name="">�� ���� Y2 ��ǥ</param>
	/// <param name="">ƨ�� ���� X -1, 0, 1�� ������ ��</param>
	/// <param name="">ƨ�� ���� Y -1, 0, 1�� ������ ��</param>
	Obstruction(double, double, double, double, double, double);
	~Obstruction();

	vector2D position2;
	vector2D nVector;
};