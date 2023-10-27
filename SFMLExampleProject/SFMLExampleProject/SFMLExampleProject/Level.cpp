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

// creates level by creating character instances based on the level array based on the supplied text file
void Level::CreateLevel()
{
	for (int x = 0; x < levelHeight; x++)
	{
		for (int y = 0; y < levelWidth; y++)
		{
			if (cLevelArray[y][x] == 'x')
			{
				Terrain* newTile = new Terrain();
				newTile->SetTerrainType(CharacterType::Wall);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}

			if (cLevelArray[y][x] == 'o')
			{
				Character* newTile = new Character();
				newTile->SetTerrainType(CharacterType::Trap);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}

			if (cLevelArray[y][x] == 'w')
			{
				Character* newTile = new Character();
				newTile->SetCharType(CharacterType::Win);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}

			if (cLevelArray[y][x] == 'p')
			{
				Character* newTile = new Character();
				newTile->SetCharType(CharacterType::Platform);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}

			if (cLevelArray[y][x] == 'c')
			{
				Character* newTile = new Character();
				newTile->SetCharType(CharacterType::Timer);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}

			if (cLevelArray[y][x] == 'd')
			{
				Character* newTile = new Character();
				newTile->SetCharType(CharacterType::Door);
				newTile->SetPosition(sf::Vector2f(x * 32, y * 32)); // sprite size
				m_LevelTiles.push_back(newTile);
			}

			if (cLevelArray[y][x] == 'b')
			{
				Character* newTile = new Character();
				newTile->SetCharType(CharacterType::Button);
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
		if (m_LevelTiles[j]->m_bEnabled)
		{
			_Window->draw(m_LevelTiles[j]->Draw());
		}
	}
}

void Level::UnloadLevel()
{
	for (int i = 0; i < m_LevelTiles.size(); i++)
	{
		delete m_LevelTiles[i];
	}
	m_LevelTiles.resize(0);
}
