#include "Board.h"

Board::Board(Level _level, int _iPlayerID)
{
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

void Board::ShowMouseSquare(sf::RenderWindow* _WindowRef)
{
	// divide mouse pos by 16 and round down to find current square then snap to that position
	float fXPos = sf::Mouse::getPosition(*_WindowRef).x;
	float fYPos = sf::Mouse::getPosition(*_WindowRef).y;

	fXPos = std::floor(fXPos / 32);
	fYPos = std::floor(fYPos / 32);

	SelectRect.setPosition(sf::Vector2f(fXPos * 32, fYPos * 32));
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
				(*it)->SetHealth((*it)->GetHealth() - playerTroop->GetDamage());
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
