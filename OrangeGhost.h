// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Game;

class OrangeGhost : public Ghost {
public:
	OrangeGhost(Game* gameInstance);
	~OrangeGhost();

	sf::Sprite* Shape();
	void Behaviour();
private:
	GhostType ghostType = GhostType::Orange;

};
