#pragma once
#ifndef BLUEGHOST_H
#define BLUEGHOST_H
#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Game;

class BlueGhost : public Ghost {
public:
	BlueGhost(Game* gameInstance);
	~BlueGhost();
	sf::Sprite* Shape();
	void Behaviour();

};

#endif
