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

	char m_cCharArray[4][15];

public:
	Troop(std::string _sFilePath);
	//Troop(int _iHealth, int _iAttackPower, int _iRange, int _iAttackRange, std::string _sType)
	//	: m_iHealth(_iHealth), m_iDamage(_iAttackPower), m_iRange(_iRange), m_iAttackRange(_iRange), m_sType(_sType) {}

	//virtual void Attack(Troop& target) = 0;
	//virtual void Defend(int damage) = 0;

	//int GetHealth() const { return m_iHealth; }
	//void SetHealth(int _health) { m_iHealth = _health; }
};

