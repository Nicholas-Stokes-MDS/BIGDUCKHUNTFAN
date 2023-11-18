// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : UIElement.h
// Description : Class responsible for all UI
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz
#pragma once
#include "SFML/Graphics.hpp"

class UIElement
{
public:
	sf::RectangleShape m_ElementVisual;
	std::string m_ElementID;

	sf::Text m_ElementText;

	UIElement(sf::Vector2f _Position, sf::Vector2f _Size, std::string _ID, sf::Font* _FontRef, sf::Color _Color);
	~UIElement();

	void ButtonReact();
	void Draw(sf::RenderWindow* _Window);
	void Update(std::string _ID);
};

