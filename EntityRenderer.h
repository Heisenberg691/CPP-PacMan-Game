#ifndef ENTITYRENDERER_H
#define ENTITYRENDERER_H
#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class EntityRenderer {
public:
	EntityRenderer();
	EntityRenderer(sf::RenderWindow* screen);
	~EntityRenderer();

	void AddEntity(Entity* entity);
	void RemoveEntity(Entity* entity);
	void RenderEntities();
	void SetRenderScreen(sf::RenderWindow* screen);
private:
	std::vector<Entity*> m_entities;
	sf::RenderWindow* m_screen;
};

#endif
