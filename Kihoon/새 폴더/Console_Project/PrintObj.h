#pragma once
#include <iostream>
#include <windows.h>

#include "text_define.h"
#include "Obstruction.h"
#include "Object.h"

class vector2D;

class PrintManager
{
private:

public:
	PrintManager();
	~PrintManager();

	void swap(double&, double&);
	void gotoxy(int, int, char);
	void printObj(Obstruction);
};