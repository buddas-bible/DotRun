#pragma once

#include<vector>
#include<iostream>
#include<Windows.h>

using namespace std;

class PixelObject;

class OutputManager
{
private:
	std::vector<std::vector<char>> charBoard;
	std::vector<std::vector<int>> colorBoard;
	std::vector<std::vector<int>> layerBoard;

	// 화면 출력 속도 개선을 위한 이전 프레임에서의 값
	std::vector<std::vector<char>> lastCharBoard;
	std::vector<std::vector<int>> lastColorBoard;

	void setColor(WORD Fontcolor, WORD BGcolor);
	void printChar(int x, int y, char ch);

public:
	OutputManager();

	void init();
	void paintScreen();
	void paintObject(const PixelObject& pixelobject);
	void paintObject(const PixelObject& pixelobject, int shift);
};