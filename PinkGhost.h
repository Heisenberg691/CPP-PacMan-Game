// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Game;

class PinkGhost : public Ghost {
public:
	PinkGhost(Game* gameInstance);
	~PinkGhost();
	sf::Sprite* Shape();
	void Behaviour();
private:
	GhostType ghostType = GhostType::Pink;
	MapCoords m_lastPacmanLocation;
};

