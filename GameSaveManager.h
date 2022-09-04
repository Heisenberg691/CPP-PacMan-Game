// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include "Globals.h"

struct GameSave
{
	uint32_t highScore = 0;
};

class Game;

class GameSaveManager {
public:
	GameSaveManager();
	GameSaveManager(Game* gameInstance);
	~GameSaveManager();

	void LoadGameSave();
	void SaveGame();
	
private:
	Game* m_gameInstance;
};
