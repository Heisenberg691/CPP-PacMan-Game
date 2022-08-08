#include "Pellet.h"

Pellet::Pellet(sf::Sprite* shape)
{
	m_shape = shape;
}

Pellet::~Pellet()
{
}

void Pellet::Draw(sf::RenderWindow* screen)
{
	screen->draw(*m_shape);
}

sf::Sprite* Pellet::Shape()
{
	return m_shape;
}
