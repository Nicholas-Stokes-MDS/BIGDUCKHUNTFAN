// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) Media Design School
//
// File Name : Terrain.h
// Description : Class responsible for processing collisions and setting character type and sprite
// Author : Nick Stokes
// Mail : Nicholas.Stokes@mds.ac.nz
#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

enum TerrainType {
	// static characters
	Wall,
	Water
};



class Terrain
{
public:
	sf::String m_sTerrainName = "Base Terrain";
	TerrainType m_TerrainType;

	void SetWindowRef(sf::RenderWindow* _Window) { m_WindowRef = _Window; }

	sf::Clock g_CharacterClock;
	int g_elapsed = 0;


	// visual elements
	sf::Sprite m_CharacterSprite;
	sf::Texture m_CharacterTexture;
	bool m_bEnabled = true;

	//movement elements
	sf::Vector2f m_CharacterPosition;
	sf::Vector2f m_CharacterVelocity;
	float m_fCharacterSpeedScalar = 30.0f;

	// Gravity
	float m_fCharacterYVelocity = 0.0f;

	// collision
	bool m_bCharacterColliding = false;
	bool m_bCharacterIsDynamic = true;
	sf::RenderWindow* m_WindowRef;

	// initialisation 
	Terrain();
	~Terrain();

	void SetTerrainType(TerrainType _Type);

	// draw
	void SetSprite(sf::String _Path);
	sf::Sprite Draw();

	// reposition
	void SetPosition(sf::Vector2f _Pos) { m_CharacterSprite.setPosition(_Pos); m_CharacterPosition = _Pos; }

	TerrainType GetTerrainType()
	{
		return m_TerrainType;
	}

	//// movement
	//void ApplyGravity(float _Grav, float _dt) { m_fCharacterYVelocity += _Grav * _dt; }
	//void Update(float _dt, std::vector<Terrain*> _CollisionObjects);

	//// physics
	//void SetDynamic(bool _Enabled) { m_bCharacterIsDynamic = _Enabled; }



//	// collision functions
//	void ProcessXCollisions(Character* _ObjA, Character* _ObjB);
//	void ProcessYCollisions(Character* _ObjA, Character* _ObjB);
//
//	void CollisionParse(CharacterType _Type);
//
//
//
//	void ResetCharacter();
//};
};
