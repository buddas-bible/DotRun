#pragma once

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;



#define ENCRYCODE 6043

#define SAVE_BESTSCORE 0
#define SAVE_DOT 1
#define SAVE_COSTUME_DATA 2
#define SAVE_UPGRADE_POINT 3
#define SAVE_UPGRADE_ITEM 4
#define SAVE_UPGRADE_TIME 5
#define SAVE_ 123




class Encryption
{
private:

public:
	Encryption();
	~Encryption();

	int Incode(int);
	int Decode(int);
};


class SaveManager
{
private:

public:
	SaveManager();
	~SaveManager();

	vector<int> Data;

	void DataSave(int, int);

	void Write();
	int Read(int);
};
