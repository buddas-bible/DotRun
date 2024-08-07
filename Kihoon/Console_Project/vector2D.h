#pragma once


class vector2D
{
public:
	vector2D();
	vector2D(double, double);
	~vector2D();

	double X, Y;

	double cross(const vector2D&) const;
	double dot(const vector2D&) const;
	vector2D operator * (double) const;
	vector2D operator + (vector2D) const;
	vector2D operator - (vector2D) const;
	bool operator == (vector2D) const;
	bool operator < (vector2D) const;
};