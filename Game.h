// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "SoundManager.h"
#include "EntityRenderer.h"
#include "Map.h"
#include "GameState.h"
#include "Globals.h"
#include "Ghost.h"
#include "ScoreBoard.h"
#include "GameSaveManager.h"
#include "Pacman.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"
#include "PinkGhost.h"
#include "RedGhost.h"

class Game {
public:
	Game();
	~Game();

	void Init();
	void Reset();
	void GameLoop();
	void LoadResources();
	void LoadMap(std::string mapName);
	void SetupPlayer();
	void Update();
	void UpdateRenderScreen();
	void SetupGhosts();
	bool IsGameFinished();
	void SetGhostsMode(GhostModes mode);
	void SetRandomScatterMode();
	void CheckStopFrightenedSoundOnFinished();
	
	TextureManager& GetTextureManager();
	AudioManager::SoundManager& GetSoundManager();
	GameState& GetGameState();
	EntityRenderer& GetEntityRenderer();
	sf::RenderWindow& GetScreen();
	Pacman& GetPlayer();
	Map& GetMap();
	std::vector<Ghost*>& GetGhosts();
	ScoreBoard& GetScoreboard();
	GameSaveManager& GetGameSaveManager();
private:
	TextureManager* m_texManager;
	AudioManager::SoundManager* m_soundManager;
	GameState* m_gameState;
	EntityRenderer* m_entityRenderer;
	sf::RenderWindow* m_screen;
	Pacman* m_player;
	Map* m_map;
	std::vector<Ghost*> m_ghosts;
	bool m_isGameResetting;
	sf::Clock m_deltaTScatterChecker;
	sf::Clock m_deltaTScatter;
	sf::Clock m_deltaTFrightened;
	bool m_isScatterModeActive;
	bool m_isFrightenedModeActive;
	int m_scatterModeDuration;
	ScoreBoard* m_scoreboard;
	GameSaveManager* m_gameSaveManager;
	
};