#include "Pacman.h"
#include "Utils.h"
#include "Game.h"
#include <iostream>

Pacman::Pacman(Game* gameInstance)
{
	m_dir = DIRECTION::UP();
	m_isDead = false;
    m_animFrameNum = 6;
    sf::Texture texture;
    m_shape = new sf::Sprite();
    m_shape->setTextureRect(sf::IntRect(CELL_SIZE * 0, CELL_SIZE * GetAnimByDirection(m_dir), CELL_SIZE, CELL_SIZE));
    sf::Vector2f newScale(GAME_SCREEN_SCALE, GAME_SCREEN_SCALE);
    m_shape->setScale(newScale);
    m_animFrame = 0;
    m_isMoving = false;
    m_screen = nullptr;
    m_gameInstance = gameInstance;
}

Pacman::~Pacman()
{
}

DIRECTION Pacman::GetDirection()
{
	return m_dir;
}

void Pacman::Draw(sf::RenderWindow* screen)
{
	screen->draw(*m_shape);
    m_screen = screen;
}

bool Pacman::IsDead()
{
	return m_isDead;
}

void Pacman::SetDead(bool dead)
{
	m_isDead = dead;
}

void Pacman::SetDirection(DIRECTION dir)
{
    m_dir = dir;
}

bool Pacman::CanGotoDirection(DIRECTION dir)
{
    return true;
}

void Pacman::SetTexture(sf::Texture* texture)
{
    m_shape->setTexture(*texture);
}

void Pacman::Move()
{
    if (!m_isMoving) {
        return;
    }
    sf::Vector2f movement = Utils::GetVector2FromDirection(m_dir);
    sf::Vector2f currentPos = m_shape->getPosition();
    float newX = currentPos.x + (movement.x * 2);
    float newY = currentPos.y + (movement.y * 2);
    

    if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
        float x = m_shape->getGlobalBounds().left;
        float y = m_shape->getGlobalBounds().top;
        if (x <= 0) {
            newX = m_screen->getSize().x-50;
        }
        else if (x >= m_screen->getSize().x) {
            newX = 10;
        }
        else if (y < 0) {
            newY = m_screen->getSize().y-50;
        }
        else if (y > m_screen->getSize().y) {
            newY = 10;
        }
        m_shape->setPosition(newX, newY);
    }
    else {
     
        unsigned int CheckDist = 20;
        if (m_dir == DIRECTION::RIGHT || m_dir == DIRECTION::LEFT) {
            for (unsigned int i = 0; i < CheckDist; i++) {
                newY = (currentPos.y + i) + (movement.y * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    m_shape->setPosition(newX, newY);
                    return;
                }
            }
            for (unsigned int i = 0; i < CheckDist; i++) {
                newY = (currentPos.y - i) + (movement.y * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    m_shape->setPosition(newX, newY);
                    return;
                }
            }
        }else if (m_dir == DIRECTION::UP || m_dir == DIRECTION::DOWN) {
            for (unsigned int i = 0; i < CheckDist; i++) {
                newX = (currentPos.x + i) + (movement.x * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    m_shape->setPosition(newX, newY);
                    return;
                }
            }
            for (unsigned int i = 0; i < CheckDist; i++) {
                newX = (currentPos.x - i) + (movement.x * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    m_shape->setPosition(newX, newY);
                    return;
                }
            }
        }  
       
    }
   
}

void Pacman::UpdateAnim()
{
    sf::Int32 DeltaTElapsedTime = m_deltaT.getElapsedTime().asMilliseconds();
    if (DeltaTElapsedTime < 50) {
        return;
    }
    m_animFrame++;
    if (m_animFrame >= m_animFrameNum) {
        m_animFrame = 0;
    }
    m_shape->setTextureRect(sf::IntRect(CELL_SIZE * m_animFrame, CELL_SIZE * GetAnimByDirection(m_dir), CELL_SIZE, CELL_SIZE));
    m_deltaT.restart();
}

unsigned int Pacman::GetAnimByDirection(DIRECTION dir)
{
    unsigned int anim = 0;

    switch (dir) {
        case RIGHT:
            anim = 0;
            break;
        case UP:
            anim = 1;
         break;
        case LEFT:
            anim = 2;
            break;
        case DOWN:
            anim = 3;
            break;
    }
    return anim;
}

sf::Sprite* Pacman::Shape()
{
    return m_shape;
}

void Pacman::CheckInteraction()
{
   // MapCoords pacmanMapCoords = m_gameInstance->m_map->GetEntityMapCoords(this,true);
    //std::cout << pacmanMapCoords.row << "," << pacmanMapCoords.col << std::endl;
    sf::FloatRect pacmanBounds = m_shape->getGlobalBounds();
    pacmanBounds.height -= 3.0;
    pacmanBounds.width -= 3.0;

    Utils::InteractionHandler<Pellet>(pacmanBounds,m_gameInstance,&(m_gameInstance->m_map->m_Pellets));
    Utils::InteractionHandler<Energizer>(pacmanBounds, m_gameInstance, &(m_gameInstance->m_map->m_Energizers));

    for (int i = 0; i < m_gameInstance->m_ghosts.size(); i++) {
        
        auto ghostShape = m_gameInstance->m_ghosts[i]->Shape();
        if (pacmanBounds.intersects(ghostShape->getGlobalBounds())) {

            if (m_gameInstance->m_ghosts[i]->m_mode == GhostModes::FRIGHTENED) {
                m_gameInstance->m_gameState.AddCurrentScore(KILLED_GHOST_POINTS_BONUS);
                m_gameInstance->m_ghosts[i]->SetMode(GhostModes::GOHOME);
                m_gameInstance->m_ghosts[i]->PlayDeadSound();
            }
            else if (m_gameInstance->m_ghosts[i]->m_mode != GhostModes::GOHOME) {
                PlayDeadSound();
                m_gameInstance->m_gameState.SetGameFinishedWithExitStatus(GameExitedStatus::DIED);
            }

            return;
        }
    }
}

void Pacman::SetCanMove(bool canMove)
{
    m_isMoving = canMove;
}

void Pacman::PlayDeadSound()
{
    auto audioId = m_gameInstance->m_soundManager.GetAudioIdByName("PacmanDead");
    m_gameInstance->m_soundManager.Play(audioId);
}

void Pacman::PlayFruitEatenSound()
{
    auto audioId = m_gameInstance->m_soundManager.GetAudioIdByName("PacmanEatFruit");
    m_gameInstance->m_soundManager.Play(audioId);
}


void Pacman::HandleInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (CanGotoDirection(DIRECTION::UP)) {
            SetDirection(DIRECTION::UP);
            m_isMoving = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if (CanGotoDirection(DIRECTION::LEFT)) {
            SetDirection(DIRECTION::LEFT);
            m_isMoving = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (CanGotoDirection(DIRECTION::DOWN)) {
            SetDirection(DIRECTION::DOWN);
            m_isMoving = true;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if (CanGotoDirection(DIRECTION::RIGHT)) {
            SetDirection(DIRECTION::RIGHT);
            m_isMoving = true;
        }
    }
    else {
        m_isMoving = false;
    }
}
