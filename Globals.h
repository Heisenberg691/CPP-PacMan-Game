#pragma once

constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char FONT_HEIGHT = 16;
constexpr float GAME_SCREEN_SCALE = 2.375;
constexpr int FRIGHTENED_MODE_TIME = 5000;
constexpr int FRIGHTENED_MODE_FLASHING_AT_MILISECONDS = 1500;
constexpr int RANDOM_SCATTER_INTERVAL_CHECK_MILISECONDS = 10000;
constexpr int SCATTER_DURATION_MIN_MILISECONDS = 5000;
constexpr int SCATTER_DURATION_MAX_MILISECONDS = 15000;
constexpr int KILLED_GHOST_POINTS_BONUS = 200;

#define GHOST_COLOR_BLUE sf::Color(0, 255, 255)
#define GHOST_COLOR_RED sf::Color(255, 0, 0)
#define GHOST_COLOR_PINK sf::Color(255, 182, 255)
#define GHOST_COLOR_ORANGE sf::Color(255, 182, 85)
#define MAP_OFFSET sf::Vector2f(0.0,50.0)

using uint = unsigned int;

struct Position
{
	short x;
	short y;

	bool operator==(const Position& i_position)
	{
		return this->x == i_position.x && this->y == i_position.y;
	}
};

enum DIRECTION { UP = 0, RIGHT, DOWN, LEFT };

enum class Cell
{
	Door,
	Empty,
	Energizer,
	Pellet,
	Wall
};

enum class GhostModes
{
	CHASE,
	FRIGHTENED,
	GOHOME,
	SCATTER
};

enum class GhostType
{
	Orange,
	Pink,
	Red,
	Blue
};

enum class GameExitedStatus
{
	DIED,
	WIN,
};

struct MapCoords {
	int row, col;

	MapCoords()
	{
		row = col = 0;
	};

	MapCoords(int r, int c)
	{
		row = r;
		col = c;
	};

	bool operator==(const MapCoords& i_position)
	{
		return this->row == i_position.row && this->col == i_position.col;
	}
	bool operator!=(const MapCoords& i_position)
	{
		return this->row != i_position.row || this->col != i_position.col;
	}
};