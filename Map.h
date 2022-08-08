#pragma once
#ifndef MAP_H
#define MAP_H
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include "Globals.h"
#include "Door.h"
#include "Pellet.h"
#include "Energizer.h"
#include "Wall.h"
#include "PathCell.h"
#include "PathFinder.h"
#include <SFML/Graphics.hpp>

class Game;

struct CellData {
	Cell type;
	Entity* entity;
};

struct MapData {
	std::vector<std::vector<CellData>> mapCellData;
	Position pacmanSpawnPoint;
	std::map < std::string, Position > ghostSpawnPoints;
	std::map < std::string, MapCoords > ghostGridSpawnPoints;
};


class Map {
public:
	Map(Game* gameInstance);
	~Map();

	std::vector<std::string> GetSketchFromFile(std::string path);
	void LoadFromFile(std::string path);
	void SetTexture(sf::Texture texture);
	void Reset();
	MapData GetMapData();
	bool HasCollisionAtCoords(float x, float y);
	MapCoords GetEntityMapCoords(Entity* entity,bool checkEmptyCells);
	MapCoords GetMapCoordsFromVector2(sf::Vector2f coords);
	void CreateCellOnMapCoords(Cell cellType, int row, int col,bool createPathCell);
	std::vector<Door*> m_Doors;
	std::vector<Wall*> m_Walls;
	std::vector<Pellet*> m_Pellets;
	std::vector<Energizer*> m_Energizers;
	std::vector<PathCell*> m_PathCells;
	PathFinder::Generator* m_pathFinder;
private:
	void GenerateShapes();
	MapData m_MapData;
	sf::Texture m_texture;
	Game* m_GameInstance;

};

#endif
