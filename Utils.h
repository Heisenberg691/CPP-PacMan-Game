// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once
#include "Game.h"

namespace Utils {

	bool AreShapesColliding(const sf::RectangleShape&, const sf::RectangleShape&);

	sf::Vector2f GetVector2FromDirection(DIRECTION dir);
	DIRECTION GetOppositeDirection(DIRECTION dir);

	int getRandomInt(int min, int max);

	template<typename T>
	void InteractionHandler(sf::FloatRect pacmanBounds, Game* gameInstance, std::vector<T*>* entityVector)
	{
		using EntityIterator = typename std::vector<T*>::iterator;

		for (EntityIterator it = entityVector->begin(); it < entityVector->end(); it++)
		{
			T* pellet = *it;

			if (pellet->Shape()->getGlobalBounds().intersects(pacmanBounds))
			{

				if (dynamic_cast<Pellet*>(pellet)) {
					gameInstance->GetGameState().AddCurrentScore(1);
				}
				else if (dynamic_cast<Energizer*>(pellet)) {
					gameInstance->SetGhostsMode(GhostModes::FRIGHTENED);
				}
				gameInstance->GetEntityRenderer().RemoveEntity(pellet);
				entityVector->erase(it);
				break;
			}
		}
	}
};

