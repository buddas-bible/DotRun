#pragma once


class vector3D
{
public:
	vector3D();
	vector3D(double, double, double);
	~vector3D();

	double X, Y, Z;

	vector3D cross(const vector3D&) const;
	vector3D operator * (double) const;
	vector3D operator + (vector3D) const;
	vector3D operator - (vector3D) const;
	bool operator == (vector3D) const;
	bool operator < (vector3D) const;
};