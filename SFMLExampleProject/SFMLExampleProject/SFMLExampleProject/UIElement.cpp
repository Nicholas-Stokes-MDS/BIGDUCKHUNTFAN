// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : UIElement.cpp
// Description : cpp file for UIElement.h
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz
#include "UIElement.h"
#include <iostream>	

// sets the position, box size, box fill color, font, font fill color, font position and font character size
UIElement::UIElement(sf::Vector2f _Position, sf::Vector2f _Size, std::string _ID, sf::Font* _FontRef, sf::Color _Color)
{
	m_ElementVisual.setPosition(_Position);
	m_ElementVisual.setSize(_Size);
	m_ElementVisual.setFillColor(sf::Color::White);

	m_ElementText.setFont(*_FontRef);
	m_ElementText.setFillColor(_Color);
	m_ElementText.setPosition(m_ElementVisual.getPosition());
	m_ElementText.setCharacterSize(24);

	m_ElementID = _ID;
	m_ElementText.setString(m_ElementID);

}

UIElement::~UIElement()
{

}

void UIElement::ButtonReact()
{
	std::cout << std::string(m_ElementText.getString()) << std::endl;
}

void UIElement::Draw(sf::RenderWindow* _Window)
{
	_Window->draw(m_ElementVisual);
	_Window->draw(m_ElementText);
}

// updates the text based on input for cases the text needs to be updated like troop number count
void UIElement::Update(std::string _ID)
{
	m_ElementID = _ID;
	m_ElementText.setString(m_ElementID);
}

