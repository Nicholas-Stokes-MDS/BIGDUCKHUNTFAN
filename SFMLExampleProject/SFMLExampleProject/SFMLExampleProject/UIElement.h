#pragma once
#include "SFML/Graphics.hpp"

class UIElement
{
public:
	sf::RectangleShape m_ElementVisual;
	std::string m_ElementID;

	sf::Text m_ElementText;

	UIElement(sf::Vector2f _Position, sf::Vector2f _Size, std::string _ID, sf::Font* _FontRef);
	~UIElement();

	void ButtonReact();
	void Draw(sf::RenderWindow* _Window);
};

