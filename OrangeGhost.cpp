#include "OrangeGhost.h"
#include "Game.h"
#include "Globals.h"
#include "Pacman.h"
#include "Utils.h"
#include <algorithm>
#include <random>

OrangeGhost::OrangeGhost(Game* gameInstance)
{
    m_dir = DIRECTION::UP();
    m_animFrameNum = 6;
    sf::Texture texture;
    m_shape = new sf::Sprite();
    m_faceShape = new sf::Sprite();
    m_shape->setTextureRect(sf::IntRect(CELL_SIZE * 1, 0, CELL_SIZE, CELL_SIZE));
    sf::Vector2f newScale(GAME_SCREEN_SCALE, GAME_SCREEN_SCALE);
    m_shape->setScale(newScale);
    m_faceShape->setScale(newScale);
    m_isMoving = false;
    m_gameInstance = gameInstance;
    m_faceShape->setTexture(*(m_gameInstance->m_texManager.getTexture("ghost")));
    m_shape->setTexture(*(m_gameInstance->m_texManager.getTexture("ghost")));
    m_shape->setColor(GHOST_COLOR_ORANGE);
    m_faceShape->setTextureRect(sf::IntRect(CELL_SIZE * 1, CELL_SIZE, CELL_SIZE, CELL_SIZE));
    m_ghostType = GhostType::Orange;
    m_isOnFinalPathDestination = false;
    m_deadSound = "PacmanEatGhost_1";
}

OrangeGhost::~OrangeGhost()
{
}


sf::Sprite* OrangeGhost::Shape()
{
    return m_shape;
}

void OrangeGhost::Behaviour()
{
    sf::Int32 DeltaTElapsedTime = m_deltaT.getElapsedTime().asMilliseconds();
    if (!m_isOnFinalPathDestination) {
        if (DeltaTElapsedTime < 5000) {
            return;
        }
    }

    MapCoords pacmanMapCoords = m_gameInstance->m_map->GetEntityMapCoords(m_gameInstance->m_player, true);
    int offset = rand() % 14 + (-7);
    auto mapCellData = m_gameInstance->m_map->GetMapData().mapCellData;
    Cell randomCellType = Cell::Wall;

    while (randomCellType == Cell::Wall) {
        pacmanMapCoords.row += offset;
        pacmanMapCoords.col += offset;

        if (pacmanMapCoords.row < 0) {
            pacmanMapCoords.row = 0;
        }
        if (pacmanMapCoords.col < 0) {
            pacmanMapCoords.col = 0;
        }
        if (pacmanMapCoords.row >= mapCellData.size()) {
            pacmanMapCoords.row = mapCellData.size()-1;
        }
        if (pacmanMapCoords.col >= mapCellData.size()) {
            pacmanMapCoords.col = mapCellData.size() - 1;
        }

        randomCellType = mapCellData[pacmanMapCoords.row][pacmanMapCoords.col].type;
        offset = rand() % 14 + (-7);
    }
   

    m_targetLocation = mapCellData[pacmanMapCoords.row][pacmanMapCoords.col].entity->Shape()->getPosition();
    m_targetMapLocation = m_gameInstance->m_map->GetEntityMapCoords(mapCellData[pacmanMapCoords.row][pacmanMapCoords.col].entity, true);

    m_deltaT.restart();
}
