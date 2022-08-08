#ifndef ENERGIZER_H
#define ENERGIZER_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Globals.h"

class Energizer : public Entity {
public:
	Energizer(sf::Sprite* shape);
	~Energizer();

	void Draw(sf::RenderWindow* screen);
	sf::Sprite* Shape();
	MapCoords m_MapLocation;
private:
	sf::Sprite* m_shape;
};

#endif
