#include "Game.h"
#include <string>

Map::Map(Game* gameInstance)
{
	m_GameInstance = gameInstance;
	m_pathFinder = new PathFinder::Generator;
}


Map::~Map()
{
}

std::vector<std::string> Map::GetSketchFromFile(std::string path)
{
	std::vector<std::string> mapSketch;
	std::ifstream mapFile(path);
	for (std::string line; std::getline(mapFile, line);)
	{
		mapSketch.push_back(line);
	}

	return mapSketch;
}

void Map::LoadFromFile(std::string path)
{
	std::vector<std::string> sketch = GetSketchFromFile(path);
	std::vector<CellData> newCell;

	for (uint32_t a = 0; a < sketch.size(); a++)
	{
		CellData newData;
		newCell.push_back(newData);
	}
	for (uint32_t b = 0; b < sketch.size(); b++)
	{
		m_MapData.mapCellData.push_back(newCell);
	}
	int mapsizeX = m_MapData.mapCellData.size();
	int mapSizeY = mapsizeX;
	m_pathFinder->setWorldSize({ mapsizeX, mapSizeY});
	m_pathFinder->setHeuristic(PathFinder::Heuristic::euclidean);
	m_pathFinder->setDiagonalMovement(false);

	for (uint32_t a = 0; a < sketch.size(); a++)
	{
		for (uint32_t b = 0; b < sketch.size(); b++)
		{
			m_MapData.mapCellData[b][a].type = Cell::Empty;

			switch (sketch[a][b])
			{
				
			case '#':
			{
				int row = a;
				int col = b;
				m_MapData.mapCellData[b][a].type = Cell::Wall;
				m_pathFinder->addCollision({col,row});
				break;
			}
			case '=':
			{
				m_MapData.mapCellData[b][a].type = Cell::Door;

				break;
			}
			case '.':
			{
				m_MapData.mapCellData[b][a].type = Cell::Pellet;

				break;
			}
			//Red ghost
			case '0':
			{
				m_MapData.ghostSpawnPoints["Red"].x = (CELL_SIZE * b * GAME_SCREEN_SCALE) +MAP_OFFSET.x;
				m_MapData.ghostSpawnPoints["Red"].y = (CELL_SIZE * a * GAME_SCREEN_SCALE) + MAP_OFFSET.y;
				m_MapData.ghostGridSpawnPoints["Red"].row = b;
				m_MapData.ghostGridSpawnPoints["Red"].col = a;
				break;
			}
			//Pink ghost
			case '1':
			{
				m_MapData.ghostSpawnPoints["Pink"].x = (CELL_SIZE * b * GAME_SCREEN_SCALE) + MAP_OFFSET.x;
				m_MapData.ghostSpawnPoints["Pink"].y = (CELL_SIZE * a * GAME_SCREEN_SCALE) + MAP_OFFSET.y;
				m_MapData.ghostGridSpawnPoints["Pink"].row = b;
				m_MapData.ghostGridSpawnPoints["Pink"].col = a;
				break;
			}
			//Blue (cyan) ghost
			case '2':
			{
				m_MapData.ghostSpawnPoints["Blue"].x = (CELL_SIZE * b * GAME_SCREEN_SCALE) + MAP_OFFSET.x;
				m_MapData.ghostSpawnPoints["Blue"].y = (CELL_SIZE * a * GAME_SCREEN_SCALE) + MAP_OFFSET.y;
				m_MapData.ghostGridSpawnPoints["Blue"].row = b;
				m_MapData.ghostGridSpawnPoints["Blue"].col = a;
				break;
			}
			//Orange ghost
			case '3':
			{
				m_MapData.ghostSpawnPoints["Orange"].x = (CELL_SIZE * b * GAME_SCREEN_SCALE) + MAP_OFFSET.x;
				m_MapData.ghostSpawnPoints["Orange"].y = (CELL_SIZE * a * GAME_SCREEN_SCALE) + MAP_OFFSET.y;
				m_MapData.ghostGridSpawnPoints["Orange"].row = b;
				m_MapData.ghostGridSpawnPoints["Orange"].col = a;
				break;
			}
			//Pacman!
			case 'P':
			{
				m_MapData.pacmanSpawnPoint.x = (CELL_SIZE * b * GAME_SCREEN_SCALE) + MAP_OFFSET.x;
				m_MapData.pacmanSpawnPoint.y = (CELL_SIZE * a * GAME_SCREEN_SCALE) + MAP_OFFSET.y;

				break;
			}
			
			case 'o':
			{
				m_MapData.mapCellData[b][a].type = Cell::Energizer;
			}
			}
		}
	}
	
	GenerateShapes();
}

void Map::GenerateShapes()
{

	for (unsigned char a = 0; a < m_MapData.mapCellData.size(); a++)
	{
		for (unsigned char b = 0; b < m_MapData.mapCellData.size(); b++)
		{
			CreateCellOnMapCoords(m_MapData.mapCellData[a][b].type, a, b,true);
		}
	}

	for (unsigned char i = 0; i < m_Walls.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().AddEntity(m_Walls[i]);
	}
	for (unsigned char i = 0; i < m_Doors.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().AddEntity(m_Doors[i]);
	}
	for (unsigned char i = 0; i < m_Pellets.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().AddEntity(m_Pellets[i]);
	}
	for (unsigned char i = 0; i < m_Energizers.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().AddEntity(m_Energizers[i]);
	}
}



void Map::SetTexture(sf::Texture texture)
{
	m_texture = texture;
}

void Map::Reset()
{
	for (unsigned char i = 0; i < m_Pellets.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().RemoveEntity(m_Pellets[i]);
	}
	for (unsigned char i = 0; i < m_Energizers.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().RemoveEntity(m_Energizers[i]);
	}
	m_Pellets.clear();
	m_Energizers.clear();

	for (unsigned char a = 0; a < m_MapData.mapCellData.size(); a++)
	{
		for (unsigned char b = 0; b < m_MapData.mapCellData.size(); b++)
		{
			if (m_MapData.mapCellData[a][b].type==Cell::Pellet || m_MapData.mapCellData[a][b].type == Cell::Energizer)
			CreateCellOnMapCoords(m_MapData.mapCellData[a][b].type, a, b,false);
		}
	}
	for (unsigned char i = 0; i < m_Pellets.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().AddEntity(m_Pellets[i]);
	}
	for (unsigned char i = 0; i < m_Energizers.size(); i++)
	{
		m_GameInstance->GetEntityRenderer().AddEntity(m_Energizers[i]);
	}
}

MapData Map::GetMapData()
{
	return m_MapData;
}

bool Map::HasCollisionAtCoords(float x, float y)
{
	sf::Sprite dummySprite;
	dummySprite.setTextureRect(sf::IntRect(CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
	sf::Vector2f newScale(GAME_SCREEN_SCALE-0.2f, GAME_SCREEN_SCALE - 0.2f);
	dummySprite.setScale(newScale);
	dummySprite.setPosition(x, y);

	for (unsigned char a = 0; a < m_MapData.mapCellData.size(); a++)
	{
		for (unsigned char b = 0; b < m_MapData.mapCellData.size(); b++)
		{
			if (m_MapData.mapCellData[a][b].type == Cell::Wall) {
				if (m_MapData.mapCellData[a][b].entity->Shape()->getGlobalBounds().intersects(dummySprite.getGlobalBounds())) {
					return true;
				}
			}

		}
	}

	return false;
}

MapCoords Map::GetEntityMapCoords(Entity* entity, bool checkEmptyCells)
{
	MapCoords mapLocation;
	mapLocation.row = 0;
	mapLocation.col = 0;

	if (checkEmptyCells)
	{
		for (unsigned char i = 0; i < m_PathCells.size(); i++)
		{
			if (m_PathCells[i]->Shape()->getGlobalBounds().intersects(entity->Shape()->getGlobalBounds())) {
				return m_PathCells[i]->m_MapLocation;
			}
		}
	}
		
	return mapLocation;
}

MapCoords Map::GetMapCoordsFromVector2(sf::Vector2f coords)
{
	MapCoords mapLocation;
	mapLocation.row = 0;
	mapLocation.col = 0;
	sf::Sprite* newShape = new sf::Sprite();
	newShape->setPosition(coords);
	sf::Vector2f newScale(GAME_SCREEN_SCALE, GAME_SCREEN_SCALE);
	newShape->setScale(newScale);

	for (unsigned char i = 0; i < m_PathCells.size(); i++)
	{
		if (m_PathCells[i]->Shape()->getGlobalBounds().intersects(newShape->getGlobalBounds())) {
			return m_PathCells[i]->m_MapLocation;
		}
	}

	return mapLocation;
}

void Map::CreateCellOnMapCoords(Cell cellType, int row, int col, bool createPathCell)
{
	sf::Sprite* newShape = new sf::Sprite();
	newShape->setTexture(m_texture);
	newShape->setPosition(static_cast<float>(CELL_SIZE * row * GAME_SCREEN_SCALE), static_cast<float>(CELL_SIZE * col * GAME_SCREEN_SCALE));
	newShape->setPosition(newShape->getPosition() + MAP_OFFSET);
	sf::Vector2f newScale(GAME_SCREEN_SCALE, GAME_SCREEN_SCALE);
	newShape->setScale(newScale);

	switch (cellType)
	{

	case Cell::Empty:
	{
		
		newShape->setTextureRect(sf::IntRect(CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
		PathCell* pathCell = new PathCell(newShape);
		pathCell->m_MapLocation.row = row;
		pathCell->m_MapLocation.col = col;
		m_MapData.mapCellData[row][col].entity = pathCell;
		m_PathCells.push_back(pathCell);
		break;
	}

	case Cell::Door:
	{
		
		newShape->setTextureRect(sf::IntRect(2 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
		Door* door = new Door(newShape);
		door->m_MapLocation.row = row;
		door->m_MapLocation.col = col;
		m_MapData.mapCellData[row][col].entity = door;
		m_Doors.push_back(door);

		if (createPathCell)
		CreateCellOnMapCoords(Cell::Empty,row, col,false);

		break;
	}

	case Cell::Energizer:
	{
		
		newShape->setTextureRect(sf::IntRect(CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
		Energizer* energizer = new Energizer(newShape);
		energizer->m_MapLocation.row = row;
		energizer->m_MapLocation.col = col;
		m_MapData.mapCellData[row][col].entity = energizer;
		m_Energizers.push_back(energizer);

		if (createPathCell)
		CreateCellOnMapCoords(Cell::Empty, row, col,false);

		break;
	}

	case Cell::Pellet:
	{
		
		newShape->setTextureRect(sf::IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));
		Pellet* pellet = new Pellet(newShape);
		pellet->m_MapLocation.row = row;
		pellet->m_MapLocation.col = col;
		m_MapData.mapCellData[row][col].entity = pellet;
		m_Pellets.push_back(pellet);

		if (createPathCell)
		CreateCellOnMapCoords(Cell::Empty, row, col,false);

		break;
	}

	case Cell::Wall:
		{
			bool down = 0;
			bool left = 0;
			bool right = 0;
			bool up = 0;

			if (col < m_MapData.mapCellData.size() - 1)
			{
				if (Cell::Wall == m_MapData.mapCellData[row][1 + col].type)
				{
					down = 1;
				}
			}


			if (0 < row)
			{
				if (Cell::Wall == m_MapData.mapCellData[row - 1][col].type)
				{
					left = 1;
				}
			}
			else
			{
				left = 1;
			}

			if (row < m_MapData.mapCellData.size() - 1)
			{
				if (Cell::Wall == m_MapData.mapCellData[1 + row][col].type)
				{
					right = 1;
				}
			}
			else
			{
				right = 1;
			}

			if (0 < col)
			{
				if (Cell::Wall == m_MapData.mapCellData[row][col - 1].type)
				{
					up = 1;
				}
			}


			newShape->setTextureRect(sf::IntRect(CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CELL_SIZE, CELL_SIZE));
			Wall* wall = new Wall(newShape);
			wall->m_MapLocation.row = row;
			wall->m_MapLocation.col = col;
			m_MapData.mapCellData[row][col].entity = wall;
			m_Walls.push_back(wall);
		}
	}
}

std::vector<PathCell*>& Map::GetPathCells()
{
	return m_PathCells;
}

PathFinder::Generator& Map::GetPathFinder()
{
	return *m_pathFinder;
}

std::vector<Door*>& Map::GetDoors()
{
	return m_Doors;
}

std::vector<Wall*>& Map::GetWalls()
{
	return m_Walls;
}

std::vector<Pellet*>& Map::GetPellets()
{
	return m_Pellets;
}

std::vector<Energizer*>& Map::GetEnergizers()
{
	return m_Energizers;
}

