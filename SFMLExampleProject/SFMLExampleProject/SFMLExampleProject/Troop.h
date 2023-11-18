// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Troop.h
// Description : Header file for Troop class. Troop class holds all information on a single troop.
// Author : Daniel West
// Mail : daniel.west@mds.ac.nz

#pragma once
#include "include/SFML/Graphics.hpp"
#include <string>
#include <fstream>
#include <iostream>

enum TroopType {

	None,
	Solider,
	Giant,
	Archer,
	Shield,
	Boat,
	Scout
};

// abstract class that all troops inherit from??
class Troop
{
protected:
	// stat members
	int m_iHealth = 0;
	int m_iDamage = 0;
	int m_iRange = 0;
	int m_iAttackRange = 0;
	std::string m_sName = "";

	// for hp
	sf::Font font;
	sf::Text hp;

	// array for searching the text file
	char m_cCharArray[5][15];

	// visual elements
	sf::Sprite m_TroopSprite;
	sf::Texture m_TroopTexture;

	// for moving 
	sf::Vector2f m_TroopPosition;

public:
	// loadis in a troops stats through a txt file
	Troop(std::string _sFilePath);
	~Troop();
	TroopType Type = None;

	bool m_bTroopMoved = false;
	bool m_bIsBuffed = false;

	// show troop health damage etc in debug
	void PrintStats();
	// sets sprite and enum based on file loaded
	void SetType();
	void SetSprite(sf::String _Path);
	// place troop
	void PlaceTroop(sf::Event _event, sf::RenderWindow* _WindowRef);
	// reposition
	void SetPosition(sf::Vector2f _Pos);
	// draw
	sf::Sprite GetSprite();
	
	// getters
	int GetHealth() { return m_iHealth; };
	int GetDamage() { return m_iDamage; };
	int GetRange() { return m_iRange; };
	int GetAttackRange() { return m_iAttackRange; };
	std::string GetName() { return m_sName; };
	sf::Vector2f GetPosition() { return m_TroopPosition; };
	sf::Text GetHpText() { return hp; };

	// setters
	void SetHealth(int _iNewHealth); //{ m_iHealth = _iNewHealth; };
	void SetDamage(int _iNewDamage) { m_iDamage = _iNewDamage; };
	void SetRange(int _iNewRange) { m_iRange = _iNewRange; };
	void SetAttackRange(int _iNewAttackRange) { m_iAttackRange = _iNewAttackRange; };

	void DisplayHP();

	//Troop(int _iHealth, int _iAttackPower, int _iRange, int _iAttackRange, std::string _sType)
	//	: m_iHealth(_iHealth), m_iDamage(_iAttackPower), m_iRange(_iRange), m_iAttackRange(_iRange), m_sType(_sType) {}

	//virtual void Attack(Troop& target) = 0;
	//virtual void Defend(int damage) = 0;

	//int GetHealth() const { return m_iHealth; }
	//void SetHealth(int _health) { m_iHealth = _health; }
};

