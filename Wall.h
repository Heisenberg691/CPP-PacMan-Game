#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Globals.h"

class Wall: public Entity {
public:
	Wall(sf::Sprite* shape);
	~Wall();

	void Draw(sf::RenderWindow* screen);
	sf::Sprite* Shape();
	MapCoords m_MapLocation;
private:
	sf::Sprite* m_shape;
};

#endif
