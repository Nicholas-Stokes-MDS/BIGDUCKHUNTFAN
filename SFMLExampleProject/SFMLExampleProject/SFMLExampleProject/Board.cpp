#include "Board.h"

Board::Board()
{
	SelectRect.setSize(sf::Vector2f(32, 32));
	// make rectangle half transparent
	SelectRect.setFillColor(sf::Color(255, 255, 255, 128));
}

void Board::MoveTroop(Troop& _Troop)
{
	// check movement range

	// check squares in movement range

	// display square showing movement range

	// ?? maybe display multiple tiles and have squares you can't move to be red ??
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
