// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
	Entity();
	~Entity();

	virtual void Draw(sf::RenderWindow* screen);
	virtual sf::Sprite* Shape();
private:
	
};

