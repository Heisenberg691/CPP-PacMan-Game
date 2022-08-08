#include "Door.h"

Door::Door(sf::Sprite* shape)
{
	m_shape = shape;
}

Door::~Door()
{
}

void Door::Draw(sf::RenderWindow* screen)
{
	screen->draw(*m_shape);
}

sf::Sprite* Door::Shape()
{
	return m_shape;
}
