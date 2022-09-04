// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Globals.h"

class PathCell : public Entity {
public:
	PathCell(sf::Sprite* shape);
	~PathCell();

	void Draw(sf::RenderWindow* screen);
	sf::Sprite* Shape();
	MapCoords m_MapLocation;
private:
	sf::Sprite* m_shape;
};
