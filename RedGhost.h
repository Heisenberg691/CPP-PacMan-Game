#pragma once
#ifndef REDGHOST_H
#define REDGHOST_H
#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Game;

class RedGhost : public Ghost {
public:
	RedGhost(Game* gameInstance);
	~RedGhost();

	sf::Sprite* Shape();
	void Behaviour();
	GhostType ghostType = GhostType::Red;
};

#endif
