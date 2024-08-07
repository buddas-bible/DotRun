#pragma once

#include <iostream>
#include <vector>

using namespace std;

class PixelObject
{
protected:
	bool isVisible;

public:
	PixelObject();
	PixelObject(int);
	~PixelObject();

	int locationX;
	int locationY;
	int sizeX;
	int sizeY;
	vector<vector<char>> Chars;
	vector<vector<int>> Colors;
	int layer;

	void init(bool _isVisible, int _locationX, int _locationY);
	void init(bool _isVisible, int _locationX, int _locationY, int _sizeX, int _sizeY, int _layer);
	void setVisible(bool _visible);
	bool getVisible() const;
	void setColor(int color);
};