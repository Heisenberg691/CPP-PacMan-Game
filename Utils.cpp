#include "Utils.h"
#include "Game.h"
#include <random>

bool Utils::AreShapesColliding(const sf::RectangleShape& a, const sf::RectangleShape& b)
{
	return a.getGlobalBounds().intersects(b.getGlobalBounds());
}

sf::Vector2f Utils::GetVector2FromDirection(DIRECTION dir)
{
	if (dir == DOWN)
	{
		return sf::Vector2f(0, 1);
	}

	if (dir == UP)
	{
		return sf::Vector2f(0, -1);
	}

	if (dir == LEFT)
	{
		return sf::Vector2f(-1, 0);
	}

	if (dir == RIGHT)
	{
		return sf::Vector2f(1, 0);
	}

	return sf::Vector2f(0, 0);
}

DIRECTION Utils::GetOppositeDirection(DIRECTION dir)
{
    DIRECTION oppositeDir = DIRECTION::UP;

    switch (dir) {
        case DIRECTION::UP:
        {
            oppositeDir = DIRECTION::DOWN;
            break;
        }
        case DIRECTION::DOWN:
        {
            oppositeDir = DIRECTION::UP;
            break;
        }
        case DIRECTION::RIGHT:
        {
            oppositeDir = DIRECTION::LEFT;
            break;
        }
        case DIRECTION::LEFT:
        {
            oppositeDir = DIRECTION::RIGHT;
            break;
        }
    }

    return oppositeDir;
}

int Utils::getRandomInt(int min, int max)
{

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
	return dist6(rng);
}