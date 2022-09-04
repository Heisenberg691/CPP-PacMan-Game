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

void GameState::SetCurrentScore(uint32_t score)
{
	m_state.score = score;

	if (m_state.score > m_state.highScore) {
		m_state.highScore = m_state.score;
	}
	SyncScoreBoard();
}

void GameState::SetHighScore(uint32_t score)
{
	m_state.highScore = score;
	SyncScoreBoard();
}

void GameState::AddCurrentScore(uint32_t score)
{
	m_state.score += score;

	if (m_state.score > m_state.highScore) {
		m_state.highScore = m_state.score;
	}
	SyncScoreBoard();
}

void GameState::SyncScoreBoard()
{
	m_gameInstance->GetScoreboard().SetCurrentScore(m_state.score);
	m_gameInstance->GetScoreboard().SetHighScore(m_state.highScore);
	m_gameInstance->GetGameSaveManager().SaveGame();
}

State& GameState::GetState()
{
	return m_state;
}

