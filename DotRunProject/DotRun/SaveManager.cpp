#pragma warning(disable:4996)

#include <iostream>
#include <stdlib.h>
#include <vector>

#include "SaveManager.h"
#include "DotRunDef.h"


SaveManager saveManager;
Encryption encryption;

Encryption::Encryption()
{
}

Encryption::~Encryption()
{
}

int Encryption::Incode(int _data)
{
	return ((rand() * ENCRYCODE) + _data);
}

int Encryption::Decode(int _data)
{
	return _data % ENCRYCODE;
}


SaveManager::SaveManager()
{
	// 벡터 초기화
	Data.resize(14, 0);
	Data[SAVE_KEY_MAXSCORE] = DEFAULT_DATA_MAXSCORE;
	Data[SAVE_KEY_DOT] = DEFAULT_DATA_DOT;
	Data[SAVE_KEY_COSTUME] = DEFAULT_DATA_COSTUME;
	Data[SAVE_KEY_UPGRADE_POINT] = DEFAULT_DATA_UPGRADE_POINT;
	Data[SAVE_KEY_UPGRADE_POWER] = DEFAULT_DATA_UPGRADE_POWER;
	Data[SAVE_KEY_UPGRADE_PROBABILITY] = DEFAULT_DATA_UPGRADE_PROBABILITY;
	Data[SAVE_KEY_COSTUME0] = DEFAULT_DATA_COSTUME0;
	Data[SAVE_KEY_COSTUME1] = DEFAULT_DATA_COSTUME1;
	Data[SAVE_KEY_COSTUME2] = DEFAULT_DATA_COSTUME2;
	Data[SAVE_KEY_COSTUME3] = DEFAULT_DATA_COSTUME3;
	Data[SAVE_KEY_COSTUME4] = DEFAULT_DATA_COSTUME4;
	Data[SAVE_KEY_COSTUME5] = DEFAULT_DATA_COSTUME5;
	Data[SAVE_KEY_COSTUME6] = DEFAULT_DATA_COSTUME6;
	Data[SAVE_KEY_COSTUME7] = DEFAULT_DATA_COSTUME7;

	FILE* Save;
	Save = fopen("Save.dat", "rb+");

	if (Save == NULL)
	{
		// 안 열리면 생성.
		Write();
		Save = fopen("Save.dat", "rb+");
	}

	// 세이브 읽어 옴
	for (int i = 0; i < Data.size(); i++)
	{
		fread(&Data[i], sizeof(int), 1, Save);
	}

	// 읽어온 세이브 해석
	/*
	for (int i = 0; i < Data.size(); i++)
	{
		Data[i] = Encry.Decode(Data[i]);
	}
	*/

	fclose(Save);
}

SaveManager::~SaveManager()
{
}

// 
void SaveManager::DataSave(int _key, int _data)
{
	if (_key < Data.size())
	{
		Data[_key] = _data;
	}
	else
	{
		Data.push_back(_data);
	}
}

// 저장하기
void SaveManager::Write()
{
	FILE* Save;
	Save = fopen("Save.dat", "wb+");
	
	/*
	for (int i = 0; i < Data.size(); i++)
	{
		Data[i] = Encry.Incode(Data[i]);
	}
	*/

	for (int i = 0; i < Data.size(); i++)
	{
		fwrite(&Data[i], sizeof(int), 1, Save);
	}

	fclose(Save);
}

// 불러오기
int SaveManager::Read(int _key)
{
	FILE* Save;
	Save = fopen("Save.dat", "rb+");

	if (Save == NULL)
	{
		Write();
		Save = fopen("Save.dat", "rb+");
	}

	for (int i = 0; i < Data.size(); i++)
	{
		fread(&Data[i], sizeof(int), 1, Save);

	}
	/*
	for (int i = 0; i < Data.size(); i++)
	{
		Data[i] = Encry.Decode(Data[i]);
	}
	*/


	fclose(Save);
	return Data[_key];
}