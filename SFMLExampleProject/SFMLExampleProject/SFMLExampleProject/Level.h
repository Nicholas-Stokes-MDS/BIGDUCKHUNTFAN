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

	// level width and height
	static const int levelWidth = 15;
	static const int levelHeight = 20;

	std::vector<Terrain*> m_LevelTiles; 
	
	// level array loaded from level text files used to create instances of terrain
	char cLevelArray[levelWidth][levelHeight];

	Level();
	~Level();

	// level creation, loading and unloading
	void LoadLevel(std::string _sFilePath);
	void CreateLevel();
	void UnloadLevel();

	// drawing
	void Draw(sf::RenderWindow* _Window);



};

