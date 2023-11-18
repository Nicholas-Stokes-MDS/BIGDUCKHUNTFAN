// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Board.cpp
// Description : Essentially player class. Handles all movement and interactions between troops
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#include "Board.h"

Board::Board(Level _level, int _iPlayerID, bool _bIsComputer)
{
	m_bIsComputer = _bIsComputer;
	SelectColour = sf::Color(255, 255, 255, 128);
	SelectRect.setSize(sf::Vector2f(32, 32));
	// make rectangle half transparent
	SelectRect.setFillColor(SelectColour);
	RangeRect.setFillColor(SelectColour);
	m_Level = _level;
}

void Board::MoveTroop(Troop& _Troop, sf::Event _event, sf::RenderWindow* _WindowRef, Board* _EnemyTroops)
{

	// check movement range

	// check squares in movement range

	// display square showing movement range

	// ?? maybe display multiple tiles and have squares you can't move to be red ??
	if (!_Troop.m_bTroopMoved)
	{
		_Troop.GetRange();
		bool bInRange = true;
		bool bAvailableSpace = false;
		int iRange = 0;
		// how far the x and y of rectange around troop is
		iRange = 64 * _Troop.GetRange() + 32;
		RangeRect.setSize(sf::Vector2f(iRange, iRange));
		// put rectangle around centre of troop
		RangeRect.setPosition(sf::Vector2f(_Troop.GetPosition().x - iRange / 2 + 16, _Troop.GetPosition().y - iRange / 2 + 16));

		// only move within range
		if (SelectRect.getGlobalBounds().intersects(RangeRect.getGlobalBounds()))
		{
			bInRange = true;
			SelectRect.setFillColor(SelectColour);
		}
		else
		{
			bInRange = false;
			SelectRect.setFillColor(sf::Color(255, 0, 0, 128));
		}

		// only move if on suitable terrain
		if (_Troop.GetName() == "Boat")
		{
			for (int i = 0; i < m_Level.m_LevelTiles.size(); i++)
			{
				if (m_Level.m_LevelTiles[i]->m_TerrainType == Water)
				{
					if (SelectRect.getGlobalBounds().intersects(m_Level.m_LevelTiles[i]->m_CharacterSprite.getGlobalBounds()))
					{
						bAvailableSpace = true;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < m_Level.m_LevelTiles.size(); i++)
			{
				if (m_Level.m_LevelTiles[i]->m_TerrainType == Wall)
				{
					if (SelectRect.getGlobalBounds().intersects(m_Level.m_LevelTiles[i]->m_CharacterSprite.getGlobalBounds()))
					{
						bAvailableSpace = true;
					}
				}
			}
		}

		// only move if no troop in the way
		for (int j = 0; j < m_Troops.size(); j++)
		{
			if (SelectRect.getGlobalBounds().intersects(m_Troops[j]->GetSprite().getGlobalBounds()))
			{
				bAvailableSpace = false;
			}
		}


		/*for (int j = 0; j < m_Troops.size(); j++)
		{
			if (SelectRect.getGlobalBounds().intersects(_EnemyTroops->m_Troops[j]->GetSprite().getGlobalBounds()))
			{
				bAvailableSpace = false;
			}
		}*/

		// only move if no enemy troops in the way
		// for loop using vector iterator
		for (auto it = _EnemyTroops->m_Troops.begin(); it != _EnemyTroops->m_Troops.end(); /* no increment here */)
		{
			// deny placement if select intersects with a troop
			for (auto& playerTroop : m_Troops)
			{
				if (SelectRect.getGlobalBounds().intersects((*it)->GetSprite().getGlobalBounds()))
				{
					bAvailableSpace = false;
				}
			}
			it++;
		}

		// place troops if conditions satisfied
		if (m_bPlacingTroops)
		{
			if (bInRange && bAvailableSpace)
			{
				_Troop.PlaceTroop(_event, _WindowRef);
			}
			else
			{
				SelectRect.setFillColor(sf::Color(255, 0, 0, 128));
			}
		}
	}
}

void Board::AddTroop(Troop* _Troop)
{
	m_Troops.push_back(_Troop);
}

bool Board::ComputerMove(Board* _EnemyTroops, bool _bForPlacment)
{
	int iTroopsMoved = 0;
	// for all troops in board
	// check a random square in range 
	// if valid square move there
	// if not valid square do not move there
	// skip turn if invalid in all squares??
	//
	// no iterator so it repeats until a spot is found
	for (auto it = m_Troops.begin(); it != m_Troops.end();)
	{
		bool bSpotAvailable = true;
		bool bCorrectTerrain = false;

		if (_bForPlacment)
		{
			if (!(*it)->m_bTroopMoved)
			{
				float fXPos = rand() % 20;
				float fYPos = rand() % 15;

				SelectRect.setPosition(fXPos * 32, fYPos * 32);
			}
		}
		else
		{
			if (!(*it)->m_bTroopMoved)
			{
				// check a random square in range
				float fXPos = rand() % ((*it)->GetRange() * 2 + 1);
				float fYPos = rand() % ((*it)->GetRange() * 2 + 1);

				// move by a random amount within range from top left of range
				SelectRect.setPosition(((*it)->GetPosition().x - ((*it)->GetRange() * 32)) + (fXPos * 32), ((*it)->GetPosition().y - ((*it)->GetRange() * 32)) + (fYPos * 32));
			}
		}
		
		// check no enemies are where the randomly selected spot is
		for (auto& enemyTroop : _EnemyTroops->m_Troops)
		{
			if (SelectRect.getGlobalBounds().intersects(enemyTroop->GetSprite().getGlobalBounds()))
			{
				bSpotAvailable = false;
			}
		}

		// check that there is a tile there
		if ((*it)->GetName() == "Boat")
		{
			for (int i = 0; i < m_Level.m_LevelTiles.size(); i++)
			{
				if (m_Level.m_LevelTiles[i]->m_TerrainType == Water)
				{
					if (SelectRect.getGlobalBounds().intersects(m_Level.m_LevelTiles[i]->m_CharacterSprite.getGlobalBounds()))
					{
						bCorrectTerrain = true;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < m_Level.m_LevelTiles.size(); i++)
			{
				if (m_Level.m_LevelTiles[i]->m_TerrainType == Wall)
				{
					if (SelectRect.getGlobalBounds().intersects(m_Level.m_LevelTiles[i]->m_CharacterSprite.getGlobalBounds()))
					{
						bCorrectTerrain = true;
					}
				}
			}
		}

		// if spot is available set troop position to test position
		if (bSpotAvailable && bCorrectTerrain)
		{
			(*it)->SetPosition(SelectRect.getPosition());
			(*it)->m_bTroopMoved = true;
			it++;
			iTroopsMoved++;
		}
	}

	if (iTroopsMoved = m_Troops.size())
	{
		return true;
	}
}

void Board::ShowMouseSquare(sf::RenderWindow* _WindowRef)
{
	// divide mouse pos by 16 and round down to find current square then snap to that position
	float fXPos = sf::Mouse::getPosition(*_WindowRef).x;
	float fYPos = sf::Mouse::getPosition(*_WindowRef).y;

	fXPos = std::floor(fXPos / 32);
	fYPos = std::floor(fYPos / 32);

	SelectRect.setPosition(sf::Vector2f(fXPos * 32, fYPos * 32));
}

void Board::ColourTroops(sf::RenderWindow& window)
{
	for (auto& troop : m_Troops) 
	{
		sf::RectangleShape rectangle(sf::Vector2f(32, 32));
		rectangle.setFillColor(sf::Color(0, 0, 255, 150));
		rectangle.setPosition(troop->GetPosition().x, troop->GetPosition().y);
		window.draw(rectangle);
	}
}

bool Board::InMovementRange(Troop& _TroopA, Troop& _TroopB)
{
	int iRange = 64 * _TroopA.GetRange() + 32;
	RangeRect.setSize(sf::Vector2f(iRange, iRange));
	// put rectangle around centre of troop
	RangeRect.setPosition(sf::Vector2f(_TroopA.GetPosition().x - iRange / 2 + 16, _TroopA.GetPosition().y - iRange / 2 + 16));

	if (_TroopB.GetSprite().getGlobalBounds().intersects(RangeRect.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

bool Board::InAttackRange(Troop& _TroopA, Troop& _TroopB)
{
	int iRange = 64 * _TroopA.GetAttackRange() + 32;
	RangeRect.setSize(sf::Vector2f(iRange, iRange));
	// put rectangle around centre of troop
	RangeRect.setPosition(sf::Vector2f(_TroopA.GetPosition().x - iRange / 2 + 16, _TroopA.GetPosition().y - iRange / 2 + 16));

	if (_TroopB.GetSprite().getGlobalBounds().intersects(RangeRect.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

void Board::AttackEnemies(Board* _EnemyBoard)
{
	//// sort through all enemy troops
	//for (int j = 0; j < _EnemyBoard->m_Troops.size(); j++)
	//{
	//	// sort through all player troops
	//	for (int i = 0; i < m_Troops.size(); i++)
	//	{
	//		// deal damage to every enemy in range
	//		if (InAttackRange(*m_Troops[i], *_EnemyBoard->m_Troops[j]))
	//		{
	//			_EnemyBoard->m_Troops[j]->SetHealth(_EnemyBoard->m_Troops[j]->GetHealth() - m_Troops[i]->GetDamage());
	//		}
	//	}
	//	if (_EnemyBoard->m_Troops[j]->GetHealth() <= 0)
	//	{
	//		// if an enemy is killed, delete that enemy and resize the vector
	//		std::cout << m_Troops[j]->GetName() << " Killed" << std::endl;
	//		delete _EnemyBoard->m_Troops[j];
	//		_EnemyBoard->m_Troops.erase(_EnemyBoard->m_Troops.begin() + j);
	//		_EnemyBoard->m_Troops.resize(_EnemyBoard->m_Troops.size() - 1);
	//	}
	//}

	// for loop using vector iterator
	for (auto it = _EnemyBoard->m_Troops.begin(); it != _EnemyBoard->m_Troops.end(); /* no increment here */) 
	{
		// deal damage to every enemy in range
		for (auto& playerTroop : m_Troops) 
		{
			if (InAttackRange(*playerTroop, **it)) 
			{
				// m_bIsBuffed adds 1 damage if true as a bool
				(*it)->SetHealth((*it)->GetHealth() - (playerTroop->GetDamage() + playerTroop->m_bIsBuffed));
			}
		}
		if ((*it)->GetHealth() <= 0) 
		{
			// if an enemy is killed, delete that enemy and remove it from the vector
			std::cout << (*it)->GetName() << " Killed" << std::endl;
			delete* it;
			it = _EnemyBoard->m_Troops.erase(it);
		}
		else 
		{
			it++;
		}
	}
}

bool Board::InVicinity(Troop* _TroopA, Troop* _TroopB)
{
	int iRange = 64 + 32;
	RangeRect.setSize(sf::Vector2f(iRange, iRange));
	// put rectangle around centre of troop
	RangeRect.setPosition(sf::Vector2f(_TroopA->GetPosition().x - iRange / 2 + 16, _TroopA->GetPosition().y - iRange / 2 + 16));

	if (_TroopB->GetSprite().getGlobalBounds().intersects(RangeRect.getGlobalBounds()))
	{
		return true;
	}
	return false;
}

void Board::BuffTroops()
{
	// for loop using vector iterator
	for (auto it = m_Troops.begin(); it != m_Troops.end(); /* no increment here */)
	{
		// check for troops in vicinity 
		for (auto& playerTroop : m_Troops)
		{
			if (InVicinity(playerTroop, *it))
			{
				(*it)->m_bIsBuffed = true;
			}
		}
		it++;
	}
}

void Board::ResetBuffs()
{
	// for loop using vector iterator
	for (auto it = m_Troops.begin(); it != m_Troops.end(); /* no increment here */)
	{
		// check for buffed troops
		for (auto& playerTroop : m_Troops)
		{
			if ((*it)->m_bIsBuffed)
			{
				(*it)->m_bIsBuffed = false;
			}
		}
		it++;
	}
}

void Board::ClearTroops()
{
	m_Troops.resize(0);
}

void Board::SetLevel(Level _level)
{
	m_Level = _level;
}

void Board::SetMouseColour(sf::Color _colour)
{
	SelectRect.setFillColor(_colour);
}
