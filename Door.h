#ifndef DOOR_H
#define DOOR_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Globals.h"

class Door : public Entity {
public:
	Door(sf::Sprite* shape);
	~Door();

	void Draw(sf::RenderWindow* screen);
	sf::Sprite* Shape();
	MapCoords m_MapLocation;
private:
	sf::Sprite* m_shape;
};

#endif
