#pragma once

#include<vector>
#include "DotRunDef.h"

class OutputManager
{
private:
	std::vector<std::vector<char>> charBoard;
	std::vector<std::vector<int>> colorBoard;
	std::vector<std::vector<int>> layerBoard;

public:
	OutputManager():
		charBoard(std::vector<std::vector<char>>(SCREEN_SIZE_X, std::vector<char>(SCREEN_SIZE_Y, ' '))),
		colorBoard(std::vector<std::vector<int>>(SCREEN_SIZE_X, std::vector<int>(SCREEN_SIZE_Y, COLOR_BASE))),			// 0000대신 색깔 초기화 필요
		layerBoard(std::vector<std::vector<int>>(SCREEN_SIZE_X, std::vector<int>(SCREEN_SIZE_Y, 0)))
	{

	}

	void paintScreen()
	{

	}

	void paintObject(PixelObject pixelobject)
	{
		int locationX; // = pixelobject.x
		int locationY; // = pixelobject.y
		int layer;



	}
};