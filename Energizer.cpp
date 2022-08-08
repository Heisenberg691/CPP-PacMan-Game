#include "Energizer.h"

Energizer::Energizer(sf::Sprite* shape)
{
	m_shape = shape;
}

Energizer::~Energizer()
{
}

void Energizer::Draw(sf::RenderWindow* screen)
{
	screen->draw(*m_shape);
}

sf::Sprite* Energizer::Shape()
{
	return m_shape;
}
