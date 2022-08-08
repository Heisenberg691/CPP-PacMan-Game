#ifndef PELLET_H
#define PELLET_H
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

#endif
