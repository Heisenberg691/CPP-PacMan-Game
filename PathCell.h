#pragma once
#ifndef PATHCELL_H
#define PATHCELL_H
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

#endif