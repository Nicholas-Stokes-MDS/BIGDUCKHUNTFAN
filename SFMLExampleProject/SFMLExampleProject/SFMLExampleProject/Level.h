// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Level.h
// Description : Class responsible for generating the level based on the supplied text file
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz
#pragma once
#include "Terrain.h"
#include <fstream>
class Level
{
public:
	int iCurrentLevel = 1;

	static const int levelWidth = 15;
	static const int levelHeight = 20;

	// functional
	std::vector<Terrain*> m_LevelTiles; // level
	

	// load file
	char cLevelArray[levelWidth][levelHeight];

	Level();
	~Level();

	void LoadLevel(std::string _sFilePath);
	void CreateLevel();
	void Draw(sf::RenderWindow* _Window);

	void UnloadLevel();
};

