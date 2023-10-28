#include "Board.h"

Board::Board(Level _level)
{
	SelectColour = sf::Color(255, 255, 255, 128);
	SelectRect.setSize(sf::Vector2f(32, 32));
	// make rectangle half transparent
	SelectRect.setFillColor(SelectColour);
	RangeRect.setFillColor(SelectColour);
	m_Level = _level;
}

void Board::MoveTroop(Troop& _Troop, sf::Event _event, sf::RenderWindow* _WindowRef)
{

	// check movement range

	// check squares in movement range

	// display square showing movement range

	// ?? maybe display multiple tiles and have squares you can't move to be red ??
	_Troop.GetRange();
	bool bInRange = true;
	bool bAvailableSpace = true;
	int iRange = 0;
	// how far the x and y of rectange around troop is
	iRange = 64 * _Troop.GetRange() + 32;
	RangeRect.setSize(sf::Vector2f(iRange, iRange));
	// put rectangle around centre of troop
	RangeRect.setPosition(sf::Vector2f(_Troop.GetPosition().x - iRange/2 + 16, _Troop.GetPosition().y - iRange/2 + 16));

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

	// only move if nothing in the way
	for (int i = 0; i < m_Level.m_LevelTiles.size(); i++)
	{
		if (SelectRect.getGlobalBounds().intersects(m_Level.m_LevelTiles[i]->m_CharacterSprite.getGlobalBounds()))
		{
			bAvailableSpace = false;
		}
	}

	if (m_bPlacingTroops)
	{
		if (bInRange && bAvailableSpace)
		{
			_Troop.PlaceTroop(_event, _WindowRef);
		}
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

bool Board::InAttackRange(Troop& _TroopA, Troop& _TroopB)
{
	return false;
}
