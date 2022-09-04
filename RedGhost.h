// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Game;

class RedGhost : public Ghost {
public:
	RedGhost(Game* gameInstance);
	~RedGhost();

	sf::Sprite* Shape();
	void Behaviour();
	
private:
	GhostType ghostType = GhostType::Red;
};
