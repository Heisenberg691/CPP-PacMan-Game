#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "Globals.h"

struct State {
	unsigned int score = 0;
	unsigned int highScore = 0;
	bool isFinished = false;
	GameExitedStatus exitedStatus = GameExitedStatus::DIED;

};

class Game;

class GameState {
public:
	GameState();
	GameState(Game* gameInstance);
	~GameState();

	State m_state;
	Game* m_gameInstance;
	void SetGameFinishedWithExitStatus(GameExitedStatus exitStatus);
	void SetCurrentScore(uint score);
	void SetHighScore(uint score);
	void AddCurrentScore(uint score);
	void SyncScoreBoard();
private:
	
};
#endif