// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Level.cpp
// Description : cpp file for Level.h
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz
#include "Level.h"
#include <iostream>

Level::Level()
{
}

Level::~Level()
{
}

// creates level array based on supplied text file
void Level::LoadLevel(std::string _sFilePath)
{
	std::fstream loadFileStream;
	loadFileStream.open(_sFilePath, std::ios::in);
	std::string loadFileString;
	int iLineCount = 0;

	/* Reminder to make sure file you are loading is the correct size */
	if (loadFileStream.is_open())
	{
		while (std::getline(loadFileStream, loadFileString))
		{
			for (int i = 0; i < loadFileString.size(); i++)
			{
				cLevelArray[iLineCount][i] = loadFileString[i];
			}

			iLineCount++;
		}

		loadFileStream.close();
	}

	CreateLevel();
}

// creates level by creating terrain instances based on the level array based on the supplied text file
void Level::CreateLevel()
{
	for (int x = 0; x < levelHeight; x++)
	{
		for (int y = 0; y < levelWidth; y++)
		{
			if (cLevelArray[y][x] == 'x')
			{
				Terrain* newTile = new Terrain();
				newTile->SetTerrainType(TerrainType::Wall);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}
			if (cLevelArray[y][x] == 'w')
			{
				Terrain* newTile = new Terrain();
				newTile->SetTerrainType(TerrainType::Water);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}
		}
	}
}

// draws level tiles
void Level::Draw(sf::RenderWindow* _Window)
{

	for (int j = 0; j < m_LevelTiles.size(); j++)
	{
		_Window->draw(m_LevelTiles[j]->Draw());
	}
}

// unloads the level
void Level::UnloadLevel()
{
	for (int i = 0; i < m_LevelTiles.size(); i++)
	{
		delete m_LevelTiles[i];
	}
	m_LevelTiles.resize(0);
}
