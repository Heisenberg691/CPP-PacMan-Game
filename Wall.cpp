#include "Wall.h"

Wall::Wall(sf::Sprite* shape)
{
	m_shape = shape;
}

Wall::~Wall()
{
}

void Wall::Draw(sf::RenderWindow* screen)
{
	screen->draw(*m_shape);
}

sf::Sprite* Wall::Shape()
{
	return m_shape;
}
