#pragma once
#include <iostream>
#include "Level.h"


class LevelManager
{
private:
	int currentLevelNum;
	int gameType;
	static LevelManager* g_LevelManagerRef; // the pointer to the manager instance
	LevelManager();

	const char* LevelList[3] =
	{
		"Levels/level1.txt",
		"Levels/level2.txt",
		"Levels/level3.txt",
	};

public:
	int g_iLevel1Troops[6] = { 1, 1, 1, 1, 1, 1 };
	int g_iLevel2Troops[6] = { 2, 0, 1, 1, 3, 0 };
	int g_iLevel3Troops[6] = { 3, 3, 1, 0, 0, 1 };
	int g_iLevel4Troops[6] = { 1, 2, 3, 4, 5, 6 };
	int g_iLevel5Troops[6] = { 6, 5, 4, 3, 2, 1 };
	int g_iLevel6Troops[6] = { 1, 3, 5, 3, 1, 0 };

	LevelManager(const LevelManager& _Manager) = delete; // when try to copy, deletes it only should be one (stops copy constructor from working)

	static LevelManager* GetInstance()
	{
		// if our instance of the manager is currently NULL we need to initialise it
		// if it is not NULL we should return it

		if (g_LevelManagerRef == NULL)
		{
			g_LevelManagerRef = new LevelManager();
			return g_LevelManagerRef;
		}
		else
		{
			return g_LevelManagerRef;
		}
	}

	void LoadLevel(int _LevelNum, Level* _LevelRef);
	void SetCurrentLevel(int _Level);
	void PrintCurrentLevel();
	int GetCurrentLevel();
	void SetGameType(int _gameType);
	int GetGameType();
};

