#include "Game.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <map>

Game::Game()
{
    m_screen = nullptr;
    m_player = nullptr;
    m_isGameResetting = false;
    m_isScatterModeActive = false;
    m_scatterModeDuration = 0;
    m_isFrightenedModeActive = false;
    m_scoreboard = new ScoreBoard(this);
    m_gameState = new GameState(this);
    m_gameSaveManager = new GameSaveManager(this);
    m_texManager = new TextureManager();
    m_soundManager = new AudioManager::SoundManager();
    m_entityRenderer = new EntityRenderer();
    m_map = new Map(this);
}
Game::~Game()
{

}

void Game::Init()
{
    m_screen = new sf::RenderWindow(sf::VideoMode(798, 850), "Pac-Man");
    m_gameSaveManager->LoadGameSave();
    UpdateRenderScreen();
    LoadResources();
    LoadMap("map_1");
    SetupPlayer();
    SetupGhosts();
    GameLoop();
}

void Game::GameLoop()
{
    sf::Context context;
    sf::Clock deltaT;
    m_screen->setFramerateLimit(60);
    while (this->m_screen->isOpen())
    {
        sf::Event event;
        while (this->m_screen->pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                this->m_screen->close();
                break;
            }
        }
       
        Update();
    }
}

void Game::LoadResources()
{
    m_texManager->loadTexture("font", "Resources/Images/Font.png");
    m_texManager->loadTexture("ghost", "Resources/Images/Ghost16.png");
    m_texManager->loadTexture("map", "Resources/Images/Map16.png");
    m_texManager->loadTexture("pacman", "Resources/Images/Pacman16.png");
    m_texManager->loadTexture("pacmandeath", "Resources/Images/PacmanDeath16.png");

    m_soundManager->Load("Resources/Sounds/PacmanEatGhost.wav", "PacmanEatGhost_0");
    m_soundManager->Load("Resources/Sounds/PacmanEatGhost.wav", "PacmanEatGhost_1");
    m_soundManager->Load("Resources/Sounds/PacmanEatGhost.wav", "PacmanEatGhost_2");
    m_soundManager->Load("Resources/Sounds/PacmanEatGhost.wav", "PacmanEatGhost_3");
    m_soundManager->Load("Resources/Sounds/PacmanDead.wav", "PacmanDead");
    m_soundManager->Load("Resources/Sounds/FrightenedMode.wav", "FrightenedMode",true);
    m_soundManager->Load("Resources/Sounds/PacmanEatFruit.wav", "PacmanEatFruit");
    m_soundManager->Load("Resources/Sounds/PacmanWin.wav", "PacmanWin");
    m_soundManager->SetVolumeAll(6.0);
    
}

void Game::LoadMap(std::string mapName)
{
    m_map->LoadFromFile("Resources/Maps/"+mapName+".txt");
    m_map->SetTexture(*GetTextureManager().getTexture("map"));
}

void Game::SetupPlayer()
{
    m_player = new Pacman(this);
    m_entityRenderer->AddEntity(m_player);
    Position pacmanSpawnPoint = m_map->GetMapData().pacmanSpawnPoint;
    sf::Vector2f pos(pacmanSpawnPoint.x, pacmanSpawnPoint.y);
    m_player->Shape()->setPosition(pos);
    m_player->SetTexture(GetTextureManager().getTexture("pacman"));
}

void Game::Update()
{
    if (!m_isGameResetting)
    {
        m_player->HandleInput();
    }

    m_screen->clear();
    m_entityRenderer->RenderEntities();
    m_scoreboard->Draw();

    if (!m_isGameResetting) {
        m_player->Move();
        m_player->UpdateAnim();
        m_player->CheckInteraction();
        SetRandomScatterMode();
        CheckStopFrightenedSoundOnFinished();
        for (uint32_t i = 0; i < m_ghosts.size(); i++) {
            m_ghosts[i]->Update();
        }

        if (IsGameFinished()) {
            Reset();
        }
    }
    
   
    m_screen->display();
}

void Game::UpdateRenderScreen()
{
    m_entityRenderer->SetRenderScreen(m_screen);
}

void Game::SetupGhosts()
{
  
    for (const auto& element : m_map->GetMapData().ghostSpawnPoints) {
       
        Position ghostPosition = m_map->GetMapData().ghostSpawnPoints[element.first];
        Ghost* ghost = nullptr;

       if (element.first == "Blue") {

            ghost = new BlueGhost(this);
            sf::Vector2f pos(ghostPosition.x, ghostPosition.y);
            ghost->SetPosition(pos);
            m_ghosts.push_back(ghost);
            m_entityRenderer->AddEntity(ghost);
            ghost->SetMoving(true);
        }
       if (element.first == "Orange") {
            ghost = new OrangeGhost(this);
            sf::Vector2f pos(ghostPosition.x, ghostPosition.y);
            ghost->SetPosition(pos);
            m_ghosts.push_back(ghost);
            m_entityRenderer->AddEntity(ghost);
            ghost->SetMoving(true);
        }
        if (element.first == "Pink") {
            ghost = new PinkGhost(this);
            sf::Vector2f pos(ghostPosition.x, ghostPosition.y);
            ghost->SetPosition(pos);
            m_ghosts.push_back(ghost);
            m_entityRenderer->AddEntity(ghost);
            ghost->SetMoving(true);
        }
        if (element.first == "Red") {
            ghost = new RedGhost(this);
            sf::Vector2f pos(ghostPosition.x, ghostPosition.y);
            ghost->SetPosition(pos);
            m_ghosts.push_back(ghost);
            m_entityRenderer->AddEntity(ghost);
            ghost->SetMoving(true);
            //ghost->SetMode(GhostModes::SCATTER);
        }
        
        
    }
   // SetGhostsMode(GhostModes::SCATTER);
}

bool Game::IsGameFinished()
{
    if (m_map->GetPellets().size() <= 0 && m_map->GetEnergizers().size() <= 0) {
       m_gameState->GetState().exitedStatus = GameExitedStatus::WIN;
       m_gameState->GetState().isFinished = true;
    }

    return m_gameState->GetState().isFinished;
}

void Game::SetGhostsMode(GhostModes mode)
{
    if (mode == GhostModes::SCATTER) {
        m_deltaTScatter.restart();
        m_scatterModeDuration = Utils::getRandomInt(SCATTER_DURATION_MIN_MILISECONDS,SCATTER_DURATION_MAX_MILISECONDS);
        m_isScatterModeActive = true;
    }
    else {
        m_isScatterModeActive = false;
        m_scatterModeDuration = 0;
    }
    for (uint32_t i = 0; i < m_ghosts.size(); i++) {
        m_ghosts[i]->SetMode(mode);
    }

    auto frightenedAudioId = m_soundManager->GetAudioIdByName("FrightenedMode");
    if (mode == GhostModes::FRIGHTENED) {
        m_deltaTFrightened.restart();
        m_isFrightenedModeActive = true;
        m_soundManager->Play(frightenedAudioId);
        auto fruitEatenAudioId = m_soundManager->GetAudioIdByName("PacmanEatFruit");
        m_soundManager->Play(fruitEatenAudioId);
    }
    else {
        m_soundManager->Stop(frightenedAudioId);
    }
}

void Game::SetRandomScatterMode()
{
    
    sf::Int32 DeltaTElapsedTimeScatter = m_deltaTScatter.getElapsedTime().asMilliseconds();
    if (m_isScatterModeActive) {
        if (DeltaTElapsedTimeScatter > m_scatterModeDuration) {
            std::cout << "STOP SCATTER" << std::endl;
            m_deltaTScatterChecker.restart();
            m_deltaTScatter.restart();
            SetGhostsMode(GhostModes::CHASE);
        }
        return;
    }
    sf::Int32 DeltaTElapsedTimeChecker = m_deltaTScatterChecker.getElapsedTime().asMilliseconds();
    if (DeltaTElapsedTimeChecker > RANDOM_SCATTER_INTERVAL_CHECK_MILISECONDS) {
   
        for (uint32_t i = 0; i < m_ghosts.size(); i++) {
            if (m_ghosts[i]->GetMode() != GhostModes::CHASE) {
                m_deltaTScatterChecker.restart();
                return;
            }
        }

        int randomNum = Utils::getRandomInt(1, 4);
       
        if (randomNum == 2) {
            std::cout << "START SCATTER" << std::endl;
            SetGhostsMode(GhostModes::SCATTER);
        }

        m_deltaTScatterChecker.restart();
    }
}

void Game::CheckStopFrightenedSoundOnFinished()
{
    if (!m_isFrightenedModeActive) {
        return;
    }
    sf::Int32 DeltaTElapsedTimeScatter = m_deltaTFrightened.getElapsedTime().asMilliseconds();
    if (DeltaTElapsedTimeScatter > FRIGHTENED_MODE_TIME) {
        m_isFrightenedModeActive = false;
        auto frightenedAudioId = m_soundManager->GetAudioIdByName("FrightenedMode");
        m_soundManager->Stop(frightenedAudioId);
    }

}

TextureManager& Game::GetTextureManager()
{
    return *m_texManager;
}

AudioManager::SoundManager& Game::GetSoundManager()
{
    return *m_soundManager;
}

GameState& Game::GetGameState()
{
    return *m_gameState;
}

EntityRenderer& Game::GetEntityRenderer()
{
    return *m_entityRenderer;
}

sf::RenderWindow& Game::GetScreen()
{
    return *m_screen;
}

Pacman& Game::GetPlayer()
{
    return *m_player;
}

Map& Game::GetMap()
{
    return *m_map;
}

std::vector<Ghost*>& Game::GetGhosts()
{
    return m_ghosts;
}

ScoreBoard& Game::GetScoreboard()
{
    return *m_scoreboard;
}

GameSaveManager& Game::GetGameSaveManager()
{
    return *m_gameSaveManager;
}

void Game::Reset()
{
    if (m_gameState->GetState().exitedStatus == GameExitedStatus::WIN) {
        auto winAudioId = m_soundManager->GetAudioIdByName("PacmanWin");
        m_soundManager->Play(winAudioId);
    }
    m_isGameResetting = true;
    m_deltaTScatter.restart();
    m_deltaTScatterChecker.restart();
    m_player->SetCanMove(false);
    m_isScatterModeActive = false;
    m_scatterModeDuration = 0;
    m_gameState = new GameState(this);
    m_gameSaveManager->LoadGameSave();
    m_gameState->SyncScoreBoard();
    Position pacmanSpawnPoint = m_map->GetMapData().pacmanSpawnPoint;
    sf::Vector2f pos(pacmanSpawnPoint.x, pacmanSpawnPoint.y);
    m_player->Shape()->setPosition(pos);
    m_map->Reset();
    for (uint32_t i = 0; i < m_ghosts.size(); i++) {
        m_entityRenderer->RemoveEntity(m_ghosts[i]);
        delete m_ghosts[i];
    }
    m_ghosts.clear();
    SetupGhosts();
    m_player->SetCanMove(true);
    m_isGameResetting = false;
    auto frightenedAudioId = m_soundManager->GetAudioIdByName("FrightenedMode");
    m_soundManager->Stop(frightenedAudioId);
}