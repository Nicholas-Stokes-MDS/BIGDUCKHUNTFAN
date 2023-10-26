#pragma once
#include "include/SFML/Graphics.hpp"
#include <string>
#include <fstream>
#include <iostream>
// abstract class that all troops inherit from
class Troop
{
protected:
	int m_iHealth;
	int m_iDamage;
	int m_iRange;
	int m_iAttackRange;
	std::string m_sName;

	char m_cCharArray[5][15];

public:
	Troop(std::string _sFilePath);

	void PrintStats();
	
	// getters
	int GetHealth() { return m_iHealth; };
	int GetDamage() { return m_iDamage; };
	int GetRange() { return m_iRange; };
	int GetAttackRange() { return m_iAttackRange; };
	std::string GetName() { return m_sName; };

	// setters
	void SetHealth(int _iNewHealth) { m_iHealth = _iNewHealth; };
	void SetDamage(int _iNewDamage) { m_iDamage = _iNewDamage; };
	void SetRange(int _iNewRange) { m_iRange = _iNewRange; };
	void SetAttackRange(int _iNewAttackRange) { m_iAttackRange = _iNewAttackRange; };

	//Troop(int _iHealth, int _iAttackPower, int _iRange, int _iAttackRange, std::string _sType)
	//	: m_iHealth(_iHealth), m_iDamage(_iAttackPower), m_iRange(_iRange), m_iAttackRange(_iRange), m_sType(_sType) {}

	//virtual void Attack(Troop& target) = 0;
	//virtual void Defend(int damage) = 0;

	//int GetHealth() const { return m_iHealth; }
	//void SetHealth(int _health) { m_iHealth = _health; }
};

