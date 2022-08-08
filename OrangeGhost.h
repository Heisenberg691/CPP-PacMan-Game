#pragma once
#ifndef ORANGEGHOST_H
#define ORANGEGHOST_H
#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Game;

class OrangeGhost : public Ghost {
public:
	OrangeGhost(Game* gameInstance);
	~OrangeGhost();

	sf::Sprite* Shape();
	void Behaviour();
	GhostType ghostType = GhostType::Orange;

};

#endif
