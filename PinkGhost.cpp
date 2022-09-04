#include "Game.h"



PinkGhost::PinkGhost(Game* gameInstance)
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
    m_shape->setColor(GHOST_COLOR_PINK);
    m_faceShape->setTextureRect(sf::IntRect(CELL_SIZE * 1, CELL_SIZE, CELL_SIZE, CELL_SIZE));
    m_ghostType = GhostType::Pink;
    m_isOnFinalPathDestination = false;
    m_deadSound = "PacmanEatGhost_2";

}

PinkGhost::~PinkGhost()
{
}


sf::Sprite* PinkGhost::Shape()
{
	return m_shape;
}

void PinkGhost::Behaviour()
{
   
    
    MapCoords pacmanMapCoords = m_gameInstance->GetMap().GetEntityMapCoords(&m_gameInstance->GetPlayer(), true);
    DIRECTION pacmanDir = m_gameInstance->GetPlayer().GetDirection();
    const int StepsInFront = 2;
    auto mapData = m_gameInstance->GetMap().GetMapData();


    switch (pacmanDir) {
        case DIRECTION::DOWN:
        {
            MapCoords DownCellCoords = pacmanMapCoords;

            for (int i = 0; i < StepsInFront; i++) {
                if (mapData.mapCellData[DownCellCoords.row][DownCellCoords.col + 1].type == Cell::Wall) {
                    break;
                }
                DownCellCoords.col++;
            }
           
            m_targetMapLocation = DownCellCoords;
            break;
        }
        case DIRECTION::UP:
        {
            MapCoords UpCellCoords = pacmanMapCoords;

            for (int i = 0; i < StepsInFront; i++) {
                if (mapData.mapCellData[UpCellCoords.row][UpCellCoords.col - 1].type == Cell::Wall) {
                    break;
                }
                UpCellCoords.col--;
            }
            m_targetMapLocation = UpCellCoords;
            break;
        }
        case DIRECTION::LEFT:
        {
            MapCoords LeftCellCoords = pacmanMapCoords;
            for (int i = 0; i < StepsInFront; i++) {
                if (LeftCellCoords.row - 1 < 0) {
                    LeftCellCoords.row = mapData.mapCellData.size()-1;
                    break;
                }
                if (mapData.mapCellData[LeftCellCoords.row-1][LeftCellCoords.col].type == Cell::Wall) {
                    break;
                }
                LeftCellCoords.row--;
            }
            m_targetMapLocation = LeftCellCoords;
            break;
        }
        case DIRECTION::RIGHT:
        {
            MapCoords RightCellCoords = pacmanMapCoords;

            for (int i = 0; i < StepsInFront; i++) {
             
                if ((RightCellCoords.row + 1)>=mapData.mapCellData.size()) {
                    RightCellCoords.row = 0;
                    break;
                }
                if (mapData.mapCellData[RightCellCoords.row + 1][RightCellCoords.col].type == Cell::Wall) {
                    break;
                }
                RightCellCoords.row++;
            }
            m_targetMapLocation = RightCellCoords;
            break;
        }
    }
    
    m_targetLocation = mapData.mapCellData[m_targetMapLocation.row][m_targetMapLocation.col].entity->Shape()->getPosition();
   
   

   // std::cout << m_targetMapLocation.row << "," << m_targetMapLocation.col << std::endl;
   
}
