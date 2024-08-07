#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PixelObject
{
private:
	bool isVisible;

public:
	PixelObject();
	~PixelObject();

	int X;
	int Y;
	int sizeX;
	int sizeY;
	vector<vector<char>> Chars;
	vector<vector<int>> Colors;
	int layer;

	bool SetVisible(bool _visible) { isVisible = _visible; }
	bool GetVisible(bool _visible) { isVisible = _visible; }
};

class CollisionObject : public PixelObject
{
	CollisionObject();
	~CollisionObject();
	void CollisionEvent() { }
};

class MessageBox : public PixelObject
{
	MessageBox();
	~MessageBox();
	void SetMessage(string) { }
	void SetBorder(char) { }
};

class Player : public CollisionObject
{
public:
	Player();
	~Player();
	CollisionEvent();
};

class Obstacle : public CollisionObject
{
public:
	Obstacle();
	~Obstacle();
	CollisionEvent();
};

class Item : public CollisionObject
{
public:
	Item();
	~Item();
	int point;
	CollisionEvent();
};
