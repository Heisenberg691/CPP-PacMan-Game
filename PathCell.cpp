#include "PathCell.h"

PathCell::PathCell(sf::Sprite* shape)
{
    m_shape = shape;
}

PathCell::~PathCell()
{
}

void PathCell::Draw(sf::RenderWindow* screen)
{
}

sf::Sprite* PathCell::Shape()
{
    return m_shape;
}
