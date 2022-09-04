// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include "Globals.h"

struct State {
	uint32_t score = 0;
	uint32_t highScore = 0;
	bool isFinished = false;
	GameExitedStatus exitedStatus = GameExitedStatus::DIED;

};

class Game;

class GameState {
public:
	GameState();
	GameState(Game* gameInstance);
	~GameState();

	void SetGameFinishedWithExitStatus(GameExitedStatus exitStatus);
	void SetCurrentScore(uint32_t score);
	void SetHighScore(uint32_t score);
	void AddCurrentScore(uint32_t score);
	void SyncScoreBoard();
	State& GetState();
private:
	Game* m_gameInstance;
	State m_state;
};