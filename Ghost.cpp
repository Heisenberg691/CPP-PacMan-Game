#include "Ghost.h"
#include "Utils.h"
#include "PinkGhost.h"
#include "Pacman.h"

Ghost::Ghost()
{
    m_dir = DIRECTION::UP();
    m_gameInstance = nullptr;
    m_screen = nullptr;
    m_shape = nullptr;
    m_faceShape = nullptr;
    m_isDead = false;
    m_isMoving = false;
    m_animFrame = 0;
    m_animFrameNum = 0;
    m_isFlashing = 0;
    m_mode = GhostModes::CHASE;
    m_ghostType = GhostType::Red;
    m_targetLocation.x = 0;
    m_targetLocation.y = 0;
    m_currentPathIndex = 0;
    m_isOnFinalPathDestination = false;
    m_deadSound = "PacmanEatGhost_0";
}

Ghost::~Ghost()
{
}

void Ghost::Draw(sf::RenderWindow* screen)
{
    if (m_mode != GhostModes::GOHOME)
    screen->draw(*m_shape);

    screen->draw(*m_faceShape);
    m_screen = screen;
}

DIRECTION Ghost::GetDirection()
{
	return m_dir;
}

sf::Sprite* Ghost::Shape()
{
	return nullptr;
}

void Ghost::Behaviour()
{
}

void Ghost::SetDirection(DIRECTION dir)
{
    m_dir = dir;
}

void Ghost::SetPosition(sf::Vector2f pos)
{
    m_shape->setPosition(pos);
    m_faceShape->setPosition(pos);
}

unsigned int Ghost::GetAnimByDirection(DIRECTION dir)
{

    if (m_mode == GhostModes::FRIGHTENED) {
        return 4;
    }
   
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

void Ghost::Update()
{
    UpdateAnim();
    UpdateMovement();
    DoModeBehaviour(m_mode);
    CheckModesExpireTime();
}

void Ghost::UpdateMovement()
{
 
    m_ghostMapLocation = m_gameInstance->m_map->GetEntityMapCoords(this, true);

    if (m_optimalPath.size()<=0) {
 
        MapCoords ghostBackMapLocation = m_ghostMapLocation;
        DIRECTION oppositeDir = Utils::GetOppositeDirection(m_dir);
        sf::Vector2f offset = Utils::GetVector2FromDirection(oppositeDir);
        ghostBackMapLocation.row += offset.x;
        ghostBackMapLocation.col += offset.y;

       
        PathFinder::CoordinateList addonCollisions;

        if (!CanGotoOppositeDirection()) {
            addonCollisions.push_back({ ghostBackMapLocation.row,ghostBackMapLocation.col });
        }
        

        if (m_ghostType == GhostType::Pink && m_mode==GhostModes::CHASE) {
           
            MapCoords pacmanMapLocation = m_gameInstance->m_map->GetEntityMapCoords(m_gameInstance->m_player, true);
            addonCollisions.push_back({ pacmanMapLocation.row,pacmanMapLocation.col});
            m_optimalPath = m_gameInstance->m_map->m_pathFinder->findPath({ m_ghostMapLocation.row, m_ghostMapLocation.col }, { m_targetMapLocation.row, m_targetMapLocation.col }, addonCollisions);
        }
        else {
            m_optimalPath = m_gameInstance->m_map->m_pathFinder->findPath({ m_ghostMapLocation.row, m_ghostMapLocation.col }, { m_targetMapLocation.row, m_targetMapLocation.col }, addonCollisions);
        }

        

       /* for (auto& _ghost : m_debugGhostPathShapes) {
            m_gameInstance->m_entityRenderer.RemoveEntity(_ghost);
        }
        m_debugGhostPathShapes.clear();
        for (auto& coordinate : *m_optimalPath) {
            Ghost* ghost = new PinkGhost(m_gameInstance);
            m_debugGhostPathShapes.push_back(ghost);
            m_gameInstance->m_entityRenderer.AddEntity(ghost);

            std::cout << "row: " << coordinate.x <<" col:"<< coordinate.y << std::endl;
            sf::Vector2f pos = m_gameInstance->m_map->GetMapData().mapCellData[coordinate.x][coordinate.y].entity->Shape()->getPosition();
            ghost->SetPosition(pos);

            
        }*/
   
    }
    

    SetDirection(GetOptimalTargetDirection());
    m_isOnFinalPathDestination = false;

    sf::Vector2f movement = Utils::GetVector2FromDirection(m_dir);
    sf::Vector2f currentPos = m_shape->getPosition();
    float newX = currentPos.x + (movement.x * 2);
    float newY = currentPos.y + (movement.y * 2);

    float dist = static_cast<float>(sqrt(pow(currentPos.x - m_targetLocation.x, 2) + pow(currentPos.y - m_targetLocation.y, 2)));

    if (dist<5) {
        m_isOnFinalPathDestination = true;
    }

    if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
        float x = m_shape->getGlobalBounds().left;
        float y = m_shape->getGlobalBounds().top;
        if (x <= 0) {
            newX = m_screen->getSize().x - 50;
        }
        else if (x >= m_screen->getSize().x) {
            newX = 10;
        }
        else if (y < 0) {
            newY = m_screen->getSize().y - 50;
        }
        else if (y > m_screen->getSize().y) {
            newY = 10;
        }
       SetPosition(sf::Vector2f(newX, newY));
    }
    else {

        unsigned int CheckDist = 20;
        if (m_dir == DIRECTION::RIGHT || m_dir == DIRECTION::LEFT) {
            for (unsigned int i = 0; i < CheckDist; i++) {
                newY = (currentPos.y + i) + (movement.y * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    SetPosition(sf::Vector2f(newX, newY));
                    return;
                }
            }
            for (unsigned int i = 0; i < CheckDist; i++) {
                newY = (currentPos.y - i) + (movement.y * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    SetPosition(sf::Vector2f(newX, newY));
                    return;
                }
            }
        }
        else if (m_dir == DIRECTION::UP || m_dir == DIRECTION::DOWN) {
            for (unsigned int i = 0; i < CheckDist; i++) {
                newX = (currentPos.x + i) + (movement.x * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    SetPosition(sf::Vector2f(newX, newY));
                    return;
                }
            }
            for (unsigned int i = 0; i < CheckDist; i++) {
                newX = (currentPos.x - i) + (movement.x * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    SetPosition(sf::Vector2f(newX, newY));
                    return;
                }
            }
        }
       

        

    }
    
    
}

void Ghost::UpdateAnim()
{
    if (m_mode == GhostModes::FRIGHTENED) {
        if (m_isFlashing) {

            sf::Int32 DeltaTElapsedTime = m_deltaTFlashing.getElapsedTime().asMilliseconds();
            if (DeltaTElapsedTime > 250) {
                m_shape->setColor(sf::Color(sf::Color::Cyan));
                m_deltaTFlashing.restart();
            }
            else {
                m_shape->setColor(sf::Color(36, 36, 255));
            }
            
        }
        else {
            m_shape->setColor(sf::Color(36, 36, 255));
        }
    }

    m_animFrame = GetAnimByDirection(m_dir);
    m_faceShape->setTextureRect(sf::IntRect(m_animFrame * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));
    
    
}

bool Ghost::CanGotoDirection(DIRECTION dir)
{

    if (m_mode != GhostModes::GOHOME) {
        if (!CanGotoOppositeDirection()) {
            DIRECTION oppositeDir = Utils::GetOppositeDirection(m_dir);

            if (oppositeDir == dir) {
                return false;
            }
        }
       
    }
   
    sf::Vector2f movement = Utils::GetVector2FromDirection(dir);
    sf::Vector2f currentPos = m_shape->getPosition();
    float newX = currentPos.x + (movement.x * 2);
    float newY = currentPos.y + (movement.y * 2);


    if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
        return true;
    }
    else {

        unsigned int CheckDist = 20;
        if (dir == DIRECTION::RIGHT || dir == DIRECTION::LEFT) {
            for (unsigned int i = 0; i < CheckDist; i++) {
                newY = (currentPos.y + i) + (movement.y * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    return true;
                }
            }
            for (unsigned int i = 0; i < CheckDist; i++) {
                newY = (currentPos.y - i) + (movement.y * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    return true;
                }
            }
        }
        else if (dir == DIRECTION::UP || dir == DIRECTION::DOWN) {
            for (unsigned int i = 0; i < CheckDist; i++) {
                newX = (currentPos.x + i) + (movement.x * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    return true;
                }
            }
            for (unsigned int i = 0; i < CheckDist; i++) {
                newX = (currentPos.x - i) + (movement.x * 2);
                if (!m_gameInstance->m_map->HasCollisionAtCoords(newX, newY)) {
                    return true;
                }
            }
        }

    }

    
    return false;
}

DIRECTION Ghost::GetOptimalTargetDirection()
{
    sf::Vector2f currentPos = m_shape->getPosition();
    DIRECTION optimalDir = DIRECTION::UP;

    if (m_optimalPath.size() <= 0) {
        return m_dir;
    }

    uint refreshPathIndex = 2;
    if (refreshPathIndex > m_optimalPath.size() - 1) {
        refreshPathIndex = m_optimalPath.size()-1;
    }

    if (m_mode != GhostModes::GOHOME) {
        if (m_currentPathIndex >= refreshPathIndex)
        {
            m_optimalPath.clear();
            m_currentPathIndex = 0;
            return m_dir;
        }
    }
   
    auto mapData = m_gameInstance->m_map->GetMapData();
    sf::Vector2f ghostPos = m_shape->getPosition();

    for (unsigned int i = 0; i < m_optimalPath.size(); i++)
    {
      
            if (m_ghostMapLocation.row == m_optimalPath.at(i).x && m_ghostMapLocation.col == m_optimalPath.at(i).y)
            {
                m_currentPathIndex = i;
              
                MapCoords DownCellCoords = m_ghostMapLocation;
                DownCellCoords.col++;
                MapCoords UpCellCoords = m_ghostMapLocation;
                UpCellCoords.col--;
                MapCoords LeftCellCoords = m_ghostMapLocation;
                LeftCellCoords.row--;
                MapCoords RightCellCoords = m_ghostMapLocation;
                RightCellCoords.row++;

               
                if ((i + 1) < m_optimalPath.size()) {

                    sf::Vector2f targetCellPos = mapData.mapCellData[m_ghostMapLocation.row][m_ghostMapLocation.col].entity->Shape()->getPosition();
                    float dist = static_cast<float>(sqrt(pow(ghostPos.x - targetCellPos.x, 2) + pow(ghostPos.y - targetCellPos.y, 2)));
               
                     if (dist > 5) {
                        
                         if (CanGotoDirection(m_dir)) {
                             //std::cout << "DIST " << dist << std::endl;
                             return m_dir;
                         }
                        
                     }

                    if (m_optimalPath[i + 1].x == DownCellCoords.row && m_optimalPath[i + 1].y == DownCellCoords.col) {
                        optimalDir = DIRECTION::DOWN;
                       // std::cout << "DOWN" << std::endl;
                    }
                    else if (m_optimalPath[i + 1].x == UpCellCoords.row && m_optimalPath[i + 1].y == UpCellCoords.col) {
                        optimalDir = DIRECTION::UP;
                       // std::cout << "UP" << std::endl;
                    }
                    else if (m_optimalPath[i + 1].x == LeftCellCoords.row && m_optimalPath[i + 1].y == LeftCellCoords.col) {
                        optimalDir = DIRECTION::LEFT;
                        //std::cout << "LEFT" << std::endl;
                    }
                    else if (m_optimalPath[i + 1].x == RightCellCoords.row && m_optimalPath[i + 1].y == RightCellCoords.col) {
                        optimalDir = DIRECTION::RIGHT;
                        //std::cout << "RIGHT" << std::endl;
                    }
                   
                    break;
                }

               
            }
    }

    if (!CanGotoDirection(optimalDir)) {
        if (m_mode == GhostModes::GOHOME) {
            TaskGoToGhostHouse();
        }
        else {
            m_optimalPath.clear();
        }
        return m_dir;
    }

    if (m_mode == GhostModes::GOHOME) {
        if (m_ghostMapLocation.row == m_optimalPath[m_optimalPath.size() - 1].x && m_ghostMapLocation.col == m_optimalPath[m_optimalPath.size() - 1].y) {
            SetMode(GhostModes::CHASE);
        }
    }

    return optimalDir;
}

void Ghost::SetMode(GhostModes mode)
{
    m_mode = mode;
    m_deltaTMode.restart();

    switch (m_mode) {
        case GhostModes::CHASE: 
           
            switch (m_ghostType) {
                    case GhostType::Red:
                        m_shape->setColor(GHOST_COLOR_RED);
                        break;
                    case GhostType::Pink:
                        m_shape->setColor(GHOST_COLOR_PINK);
                        break;
                    case GhostType::Blue:
                        m_shape->setColor(GHOST_COLOR_BLUE);
                        break;
                    case GhostType::Orange:
                        m_shape->setColor(GHOST_COLOR_ORANGE);
                        break;

                }
            break;

        case GhostModes::FRIGHTENED:

            SetDirection(Utils::GetOppositeDirection(m_dir));
            m_shape->setColor(sf::Color(36, 36, 255));
            if (m_optimalPath.size() == 0) {
               
                TaskGoToRandomLocation();
                break;
            }
            m_targetMapLocation.row = m_optimalPath[0].x;
            m_targetMapLocation.col = m_optimalPath[0].y;
            m_targetLocation = m_gameInstance->m_map->GetMapData().mapCellData[m_targetMapLocation.row][m_targetMapLocation.col].entity->Shape()->getPosition();
            m_optimalPath.clear();
            m_currentPathIndex = 0;
            break;

        case GhostModes::GOHOME:
            TaskGoToGhostHouse();
            break;
        case GhostModes::SCATTER:
            m_optimalPath.clear();
            break;
    }
}

void Ghost::SetMoving(bool isMoving)
{
    m_isMoving = isMoving;
}

void Ghost::CheckModesExpireTime()
{
    if (m_mode == GhostModes::FRIGHTENED) {
        
         sf::Int32 DeltaTElapsedTime = m_deltaTMode.getElapsedTime().asMilliseconds();
            if (DeltaTElapsedTime < (FRIGHTENED_MODE_TIME- FRIGHTENED_MODE_FLASHING_AT_MILISECONDS)) {
                 m_deltaTFlashing.restart();
                 m_isFlashing = true;
                 return;
            }
            if (DeltaTElapsedTime < FRIGHTENED_MODE_TIME) {
                return;
            }
            if (m_optimalPath.size() == 0) {
                return;
            }
            m_isFlashing = false;
            SetMode(GhostModes::CHASE);
            m_targetMapLocation.row = m_optimalPath[0].x;
            m_targetMapLocation.col = m_optimalPath[0].y;
            m_targetLocation = m_gameInstance->m_map->GetMapData().mapCellData[m_targetMapLocation.row][m_targetMapLocation.col].entity->Shape()->getPosition();
            m_optimalPath.clear();
            m_currentPathIndex = 0;
            m_deltaTMode.restart();
    }
    
}

void Ghost::DoModeBehaviour(GhostModes mode)
{
    switch (mode) {
        case GhostModes::FRIGHTENED:
        {
            TaskGoToRandomLocation();
            break;
        }
        case GhostModes::CHASE:
        {
            Behaviour();
            break;
        }
        case GhostModes::SCATTER:
        {
            ScatterBehaviour();
            break;
        }
    }
}

void Ghost::TaskGoToRandomLocation()
{
    auto paths = m_gameInstance->m_map->m_PathCells;
    int randomPathIndex = Utils::getRandomInt(0, paths.size() - 1);
    m_targetLocation = paths[randomPathIndex]->Shape()->getPosition();
    m_targetMapLocation = m_gameInstance->m_map->GetEntityMapCoords(paths[randomPathIndex], true);
}

void Ghost::TaskGoToGhostHouse()
{
    auto mapdata = m_gameInstance->m_map->GetMapData();
    m_targetLocation.x = mapdata.ghostSpawnPoints["Blue"].x;
    m_targetLocation.y = mapdata.ghostSpawnPoints["Blue"].y;
    m_targetMapLocation = mapdata.ghostGridSpawnPoints["Blue"];
    m_optimalPath.clear();
    m_currentPathIndex = 0;
}

void Ghost::ScatterBehaviour()
{
   
    switch (m_ghostType) {
        case GhostType::Red:
        {
            m_targetMapLocation.row = 17;
            m_targetMapLocation.col = 1;
            if (m_ghostMapLocation == m_targetMapLocation) {
                m_targetMapLocation.row = 18;
                m_targetMapLocation.col = 5;
                if (m_dir==DIRECTION::UP)
                SetDirection(DIRECTION::DOWN);
            }

            break;
        }
        case GhostType::Pink:
        {
            m_targetMapLocation.row = 3;
            m_targetMapLocation.col = 1;
            if (m_ghostMapLocation == m_targetMapLocation) {
                m_targetMapLocation.row = 2;
                m_targetMapLocation.col = 5;
                if (m_dir == DIRECTION::UP)
                SetDirection(DIRECTION::DOWN);
            }

            break;
        }
        case GhostType::Orange:
        {
            m_targetMapLocation.row = 2;
            m_targetMapLocation.col = 19;
            if (m_ghostMapLocation == m_targetMapLocation) {
                m_targetMapLocation.row = 18;
                m_targetMapLocation.col = 19;
                if (m_dir == DIRECTION::LEFT)
                SetDirection(DIRECTION::RIGHT);
            }

            break;
        }
        case GhostType::Blue:
        {
            m_targetMapLocation.row = 18;
            m_targetMapLocation.col = 19;
            if (m_ghostMapLocation == m_targetMapLocation) {
                m_targetMapLocation.row = 2;
                m_targetMapLocation.col = 19;
                if (m_dir == DIRECTION::RIGHT)
                SetDirection(DIRECTION::LEFT);
            }

            break;
        }
    }

    m_targetLocation = m_gameInstance->m_map->GetMapData().mapCellData[m_targetMapLocation.row][m_targetMapLocation.col].entity->Shape()->getPosition();
 
}

void Ghost::PlayDeadSound()
{
    auto audioId = m_gameInstance->m_soundManager.GetAudioIdByName(m_deadSound);
    m_gameInstance->m_soundManager.Play(audioId);
}

bool Ghost::CanGotoOppositeDirection()
{
    auto mapData = m_gameInstance->m_map->GetMapData();
    if (m_ghostMapLocation == mapData.ghostGridSpawnPoints["Blue"] || m_ghostMapLocation == mapData.ghostGridSpawnPoints["Pink"] ||
        m_ghostMapLocation == mapData.ghostGridSpawnPoints["Orange"])
    {
        return true;
    }

    return false;
    
}
