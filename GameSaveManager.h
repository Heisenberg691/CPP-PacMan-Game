#pragma once
#ifndef GAMESAVEMANAGER_H
#define GAMESAVEMANAGER_H
#include "Globals.h"

struct GameSave
{
	uint highScore = 0;
};

class Game;

class GameSaveManager {
public:
	GameSaveManager();
	GameSaveManager(Game* gameInstance);
	~GameSaveManager();

	void LoadGameSave();
	void SaveGame();
	Game* m_gameInstance;
private:

};

#endif
