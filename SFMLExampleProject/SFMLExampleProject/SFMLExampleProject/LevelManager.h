// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : LevelManager.h
// Description : Singleton class responsible for handling global variables that uses data orientated programming using text files
//				 and can load levels using the Level class
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz

#pragma once
#include <iostream>
#include "Level.h"


class LevelManager
{
private:
	// global variables
	int currentLevelNum;
	int gameType;
	int resolution;
	// global variables

	static LevelManager* g_LevelManagerRef; // the pointer to the manager instance
	LevelManager();

	const char* LevelList[6] =
	{
		"Levels/level1.txt",
		"Levels/level2.txt",
		"Levels/level3.txt",
		"Levels/level4.txt",
		"Levels/level5.txt",
		"Levels/level6.txt"
	};

public:
	// The order is Archer, Boat, Giant, Scout, Shield, Soldier
	int g_iLevel1Troops[6] = { 0, 0, 0, 0, 0, 4 };
	int g_iLevel2Troops[6] = { 3, 0, 0, 0, 3, 0 };
	int g_iLevel3Troops[6] = { 3, 0, 0, 2, 3, 4 };
	int g_iLevel4Troops[6] = { 0, 1, 0, 2, 0, 4 };
	int g_iLevel5Troops[6] = { 2, 0, 2, 3, 0, 0 };
	//int g_iLevel6Troops[6] = { 4, 2, 2, 3, 4, 6 };
	int g_iLevel6Troops[6] = { 3, 1, 1, 2, 3, 4};

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
	void SetResolution(int _resolution);
	int GetResolution();
};

