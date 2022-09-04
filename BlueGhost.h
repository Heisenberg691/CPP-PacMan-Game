// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

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

