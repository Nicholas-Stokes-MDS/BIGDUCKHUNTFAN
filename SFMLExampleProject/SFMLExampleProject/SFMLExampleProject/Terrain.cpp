// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Terrain.cpp
// Description : cpp file for Terrain.h
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz
#include "Terrain.h"


Terrain::Terrain()
{

}

Terrain::~Terrain()
{
}


// sets terrain's sprite based on terrain type supplied 
void Terrain::SetTerrainType(TerrainType _Type)
{
	switch (_Type)
	{
	case Wall:
		SetSprite("Sprites/DefaultBlock.bmp");
		break;
	case Water:
		SetSprite("Sprites/WaterTile.bmp");
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