#pragma once
#include <vector>
#include "text_define.h"
#include "vector2D.h"

using namespace std;


class Object
{
private:

public:
	vector2D position;
	
	Object();
	Object(double, double);
	~Object();

};