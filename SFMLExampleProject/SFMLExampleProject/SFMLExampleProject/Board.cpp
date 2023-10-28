#include "Board.h"

Board::Board()
{
	SelectColour = sf::Color(255, 255, 255, 128);
	SelectRect.setSize(sf::Vector2f(32, 32));
	// make rectangle half transparent
	SelectRect.setFillColor(SelectColour);
	RangeRect.setFillColor(SelectColour);
}

void Board::MoveTroop(Troop& _Troop, sf::Event _event, sf::RenderWindow* _WindowRef)
{

	// check movement range

	// check squares in movement range

	// display square showing movement range

	// ?? maybe display multiple tiles and have squares you can't move to be red ??
	_Troop.GetRange();
	bool bInRange = false;
	int iRange = 0;
	iRange = 32 * _Troop.GetRange() * 3;
	RangeRect.setSize(sf::Vector2f(iRange, iRange));
	// put rectangle around centre of troop
	RangeRect.setPosition(sf::Vector2f(_Troop.GetPosition().x - iRange/2 + 16, _Troop.GetPosition().y - iRange/2 + 16));

	if (m_bPlacingTroops)
	{
		if (bInRange)
		{
			_Troop.PlaceTroop(_event, _WindowRef);
		}
		else
		{
			SelectRect.setFillColor(sf::Color(255, 0, 0, 128));
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
