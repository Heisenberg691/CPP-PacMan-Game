// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Globals.h"

class Pellet : public Entity {
public:
	Pellet(sf::Sprite* shape);
	~Pellet();

	void Draw(sf::RenderWindow* screen);
	sf::Sprite* Shape();
	MapCoords m_MapLocation;
private:
	sf::Sprite* m_shape;
};
