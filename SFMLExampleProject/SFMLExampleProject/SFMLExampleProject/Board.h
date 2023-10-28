// takes level array and creates board. Manages mouse clicks and troop placement. 

#pragma once
#include "Level.h"
#include "Troop.h"
#include "Terrain.h"

class Board
{
protected:
	sf::RectangleShape RangeRect;
	sf::RectangleShape SelectRect;
	sf::Color SelectColour;
	bool m_bPlacingTroops = true;

public:
	Board();
	~Board();

	void MoveTroop(Troop& _Troop, sf::Event _event, sf::RenderWindow* _WindowRef);

	// creates a square with low opacity that snaps to whichever tile the mouse is inside
	void ShowMouseSquare(sf::RenderWindow* _WindowRef);

	void DrawBoard(sf::RenderWindow* _Window);


	bool InAttackRange(Troop& _TroopA, Troop& _TroopB);

	// getters
	sf::RectangleShape GetSelectRect() { return SelectRect; };
	sf::RectangleShape GetRangeRect() { return RangeRect; };
	bool IsPlacingTroops() { return m_bPlacingTroops; };
};

