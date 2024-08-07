#pragma once

#include "PixelObject.h"
using namespace std;

class MessageObject : public PixelObject
{
private:
	int alignment;
	int fontcolor;
	int bgcolor;
	int borderbgcolor;

public:
	MessageObject();
	MessageObject(string msg, int _alignment, int _fontcolor, int _bgcolor, int _borderbgcolor, int _locationX, int _locationY, int _sizeX, int _sizeY, int _layer);
	~MessageObject();
	void SetMessage(string);
	void SetBorder(char);
	void SetSizeX(int);
};