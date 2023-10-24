#pragma once
#include <string>
// abstract class that all troops inherit from
class Troop
{
protected:
	int m_iHealth;
	int m_iDamage;
	int m_iRange;
	int m_iAttackRange;
	std::string m_sType;

public:
	Troop(int _iHealth, int _iAttackPower, int _iRange, int _iAttackRange, std::string _sType)
		: m_iHealth(_iHealth), m_iDamage(_iAttackPower), m_iRange(_iRange), m_iAttackRange(_iRange), m_sType(_sType) {}

	virtual void Attack(Troop& target) = 0;
	virtual void Defend(int damage) = 0;
	virtual void Move(int x, int y) = 0;

	int GetHealth() const { return m_iHealth; }
	void SetHealth(int _health) { m_iHealth = _health; }
};

