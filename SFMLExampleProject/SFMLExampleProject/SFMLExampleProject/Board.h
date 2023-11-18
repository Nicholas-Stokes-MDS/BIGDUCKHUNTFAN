// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Board.h
// Description : Header file for Board class. Handles troop placement, troop movement and interactions between troops.
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#pragma once
#include "Level.h"
#include "Troop.h"
#include "Terrain.h"
#include <algorithm>

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
	// check if player is computer player
	bool m_bIsComputer;

	// vector holding all the troop
	std::vector<Troop*> m_Troops;

	Board(Level _level, int _iPlayerID, bool _bIsComputer);
	~Board();

	void MoveTroop(Troop& _Troop, sf::Event _event, sf::RenderWindow* _WindowRef, Board* _EnemyTroops);
	void AddTroop(Troop* _Troop);

	// automatically move troops
	bool ComputerMove(Board* _EnemyTroops, bool _bForPlacement);

	// creates a square with low opacity that snaps to whichever tile the mouse is inside
	void ShowMouseSquare(sf::RenderWindow* _WindowRef);

	// colour enemy troops to make it obvious who is who
	void ColourTroops(sf::RenderWindow& window);

	bool InMovementRange(Troop& _TroopA, Troop& _TroopB);
	bool InAttackRange(Troop& _TroopA, Troop& _TroopB);
	void AttackEnemies(Board* _EnemyBoard);

	// buff troops in direct viscinity 
	bool InVicinity(Troop* _TroopA, Troop* _TroopB);
	void BuffTroops();
	void ResetBuffs();

	void ClearTroops();

	// getters
	sf::RectangleShape GetSelectRect() { return SelectRect; };
	sf::RectangleShape GetRangeRect() { return RangeRect; };
	bool IsPlacingTroops() { return m_bPlacingTroops; };

	// setters
	void SetLevel(Level _level);
	void SetMouseColour(sf::Color _colour);
};

