#include "UIElement.h"
#include <iostream>	
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

void UIElement::Update(std::string _ID)
{
	m_ElementID = _ID;
	m_ElementText.setString(m_ElementID);
}

