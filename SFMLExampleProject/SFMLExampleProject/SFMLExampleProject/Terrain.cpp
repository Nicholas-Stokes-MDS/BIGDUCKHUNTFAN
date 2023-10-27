// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Character.cpp
// Description : cpp file for Character.h
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz
#include "Terrain.h"
// default constuctor setting sprite and position
Terrain::Terrain()
{
	SetSprite("Images/Sprites/PlayerBlock.bmp");
	m_CharacterSprite.setOrigin(m_CharacterTexture.getSize().x / 2, m_CharacterTexture.getSize().y / 2);
	m_CharacterPosition = sf::Vector2f(40, 400);
	m_CharacterSprite.setPosition(m_CharacterPosition);
}

Terrain::~Terrain()
{
}


// sets character's sprite and if it is dynamic based on the character type supplied
void Terrain::SetTerrainType(TerrainType _Type)
{
	switch (_Type)
	{
	case Wall:
		SetSprite("Images/Sprites/DefaultBlock.bmp");
		break;
	default:
		break;
	}

	m_TerrainType = _Type;
}

void Terrain::SetSprite(sf::String _Path)
{
	m_CharacterTexture.loadFromFile(_Path);
	m_CharacterSprite.setTexture(m_CharacterTexture);
}

sf::Sprite Terrain::Draw()
{
	return m_CharacterSprite;
}