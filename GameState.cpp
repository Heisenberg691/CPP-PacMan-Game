#include "GameState.h"
#include "Game.h"

GameState::GameState()
{
	m_gameInstance = nullptr;
}

GameState::GameState(Game* gameInstance)
{
	m_gameInstance = gameInstance;
}

GameState::~GameState()
{
}

void GameState::SetGameFinishedWithExitStatus(GameExitedStatus exitStatus)
{
	m_state.exitedStatus = exitStatus;
	m_state.isFinished = true;
}

void GameState::SetCurrentScore(uint score)
{
	m_state.score = score;

	if (m_state.score > m_state.highScore) {
		m_state.highScore = m_state.score;
	}
	SyncScoreBoard();
}

void GameState::SetHighScore(uint score)
{
	m_state.highScore = score;
	SyncScoreBoard();
}

void GameState::AddCurrentScore(uint score)
{
	m_state.score += score;

	if (m_state.score > m_state.highScore) {
		m_state.highScore = m_state.score;
	}
	SyncScoreBoard();
}

void GameState::SyncScoreBoard()
{
	m_gameInstance->m_scoreboard->SetCurrentScore(m_state.score);
	m_gameInstance->m_scoreboard->SetHighScore(m_state.highScore);
	m_gameInstance->m_gameSaveManager->SaveGame();
}

