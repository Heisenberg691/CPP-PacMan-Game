#include "EntityRenderer.h"

EntityRenderer::EntityRenderer()
{
	m_screen = nullptr;
}

EntityRenderer::EntityRenderer(sf::RenderWindow* screen)
{
	m_screen = screen;
}

EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
}

void EntityRenderer::RemoveEntity(Entity* entity)
{
	for (std::vector<Entity*>::iterator it_second = m_entities.begin(); it_second < m_entities.end(); it_second++) {

		if (*it_second == entity) {
			m_entities.erase(it_second);
			break;
		}
	}
}

void EntityRenderer::RenderEntities()
{
	for (uint32_t i = 0; i < m_entities.size(); i++) {
		m_entities[i]->Draw(m_screen);
	}
}

void EntityRenderer::SetRenderScreen(sf::RenderWindow* screen)
{
	m_screen = screen;
}
