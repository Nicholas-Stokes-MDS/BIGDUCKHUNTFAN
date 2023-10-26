// takes level array and creates board. Manages mouse clicks and troop placement. 

#pragma once
#include "Level.h"
#include "Troop.h"
#include "Terrain.h"

class Board
{
protected:
	
public:
	void MoveTroop(Troop& _Troop);

	// creates a square with low opacity that snaps to whichever tile the mouse is inside
	void ShowMouseSquare();

	void DrawBoard(sf::RenderWindow* _Window);

	bool InAttackRange(Troop& _TroopA, Troop& _TroopB);
};

