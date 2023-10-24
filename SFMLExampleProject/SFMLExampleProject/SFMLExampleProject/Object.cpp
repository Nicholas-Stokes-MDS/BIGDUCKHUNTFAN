#include "Object.h"

Object::Object(ObjectType _Type, sf::Vector2f _Position) // constructor. Each object has a type and position. 
{
	m_ObjShape.setSize(sf::Vector2f(30, 30));
	m_ObjShape.setPosition(_Position);
	
	// this switch statement allows us to change the colour based on the object type, which is part of the object constructor, above. 
	switch (_Type)
	{
		
		case Type_Trap:
			m_ObjShape.setFillColor(sf::Color::Red);
			break;
		case Type_Player:
			m_ObjShape.setFillColor(sf::Color::Blue);
			break;
		case Type_Goal:
			m_ObjShape.setFillColor(sf::Color::Yellow);
			break;
			
		default:
			break;
	}
}

Object::~Object()
{
}

void Object::Update()
{
}

void Object::Input()
{
	m_ObjSpeed = sf::Vector2f(0, 0);

	m_ObjShape.move(m_ObjSpeed);
}
