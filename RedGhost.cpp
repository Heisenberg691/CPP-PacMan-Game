#include "RedGhost.h"
#include "Game.h"
#include "Globals.h"
#include "Pacman.h"
#include "PathFinder.h"

RedGhost::RedGhost(Game* gameInstance)
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
    m_shape->setColor(GHOST_COLOR_RED);
    m_faceShape->setTextureRect(sf::IntRect(CELL_SIZE * 1, CELL_SIZE, CELL_SIZE, CELL_SIZE));
    m_ghostType = GhostType::Red;
    m_isOnFinalPathDestination = false;
    m_deadSound = "PacmanEatGhost_3";

}

RedGhost::~RedGhost()
{
}


sf::Sprite* RedGhost::Shape()
{
    return m_shape;
}

void RedGhost::Behaviour()
{

    m_targetLocation = m_gameInstance->m_player->Shape()->getPosition();
    m_targetMapLocation = m_gameInstance->m_map->GetEntityMapCoords(m_gameInstance->m_player, true);
   
}
