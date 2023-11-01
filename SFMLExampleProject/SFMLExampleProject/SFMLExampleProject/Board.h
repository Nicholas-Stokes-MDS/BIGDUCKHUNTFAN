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
	Level m_Level;
	int m_iPlayerID = 0;

public:
	// vector holding all the troop
	std::vector<Troop*> m_Troops;

	Board(Level _level, int _iPlayerID);
	~Board();

	void MoveTroop(Troop& _Troop, sf::Event _event, sf::RenderWindow* _WindowRef);
	void AddTroop(Troop* _Troop);

	// creates a square with low opacity that snaps to whichever tile the mouse is inside
	void ShowMouseSquare(sf::RenderWindow* _WindowRef);

	void DrawBoard(sf::RenderWindow* _Window);


	bool InAttackRange(Troop& _TroopA, Troop& _TroopB);
	void AttackEnemies(Board* _EnemyBoard);

	// getters
	sf::RectangleShape GetSelectRect() { return SelectRect; };
	sf::RectangleShape GetRangeRect() { return RangeRect; };
	bool IsPlacingTroops() { return m_bPlacingTroops; };
};

