#pragma once
#ifndef PINKGHOST_H
#define PINKGHOST_H
#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Game;

class PinkGhost : public Ghost {
public:
	PinkGhost(Game* gameInstance);
	~PinkGhost();
	sf::Sprite* Shape();
	void Behaviour();
	GhostType ghostType = GhostType::Pink;
	MapCoords m_lastPacmanLocation;
};

#endif
