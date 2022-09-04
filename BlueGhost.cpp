#include "Game.h"

BlueGhost::BlueGhost(Game* gameInstance)
{
    m_dir = DIRECTION(0);
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
    m_faceShape->setTexture(*(m_gameInstance->GetTextureManager().getTexture("ghost")));
    m_shape->setTexture(*(m_gameInstance->GetTextureManager().getTexture("ghost")));
    m_shape->setColor(GHOST_COLOR_BLUE);
    m_faceShape->setTextureRect(sf::IntRect(CELL_SIZE * 1,CELL_SIZE,CELL_SIZE,CELL_SIZE));
    m_ghostType = GhostType::Blue;
    m_isOnFinalPathDestination = false;
    m_deadSound = "PacmanEatGhost_0";
}

BlueGhost::~BlueGhost()
{
}


sf::Sprite* BlueGhost::Shape()
{
    return m_shape;
}

void BlueGhost::Behaviour()
{
    sf::Int32 DeltaTElapsedTime = m_deltaT.getElapsedTime().asMilliseconds();
    if (!m_isOnFinalPathDestination) {
        if (DeltaTElapsedTime < 5000) {
            return;
        }
    }
   

    TaskGoToRandomLocation();

    m_deltaT.restart();
}
