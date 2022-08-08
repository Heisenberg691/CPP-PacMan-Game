#pragma once
#ifndef GAME_H
#define GAME_H
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

class Pacman;

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
	TextureManager m_texManager;
	AudioManager::SoundManager m_soundManager;
	GameState m_gameState;
	EntityRenderer m_entityRenderer;
	sf::RenderWindow* m_screen;
	Pacman* m_player;
	Map* m_map = new Map(this);
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

private:
	
};

#endif
