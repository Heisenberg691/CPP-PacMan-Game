#define _CRT_SECURE_NO_WARNINGS
#include "GameSaveManager.h"
#include "Game.h"
#include <iostream>
#include <fstream>

GameSaveManager::GameSaveManager()
{
	m_gameInstance = nullptr;
}

GameSaveManager::GameSaveManager(Game* gameInstance)
{
	m_gameInstance = gameInstance;
}

GameSaveManager::~GameSaveManager()
{
}

void GameSaveManager::LoadGameSave()
{
	char filename[] = "Resources/GameSaves/GameSave.pacman";
	std::fstream appendFileToWorkWith;
	appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
	if (!appendFileToWorkWith)
	{
		appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
		appendFileToWorkWith << "";
		appendFileToWorkWith.close();
	}
	GameSave saveData;
	FILE* fin = fopen("Resources/GameSaves/GameSave.pacman", "r");
	fread(&saveData, sizeof(GameSave), 1, fin);
	printf("%d\n", saveData.highScore);
	fclose(fin);

	m_gameInstance->m_gameState.SetHighScore(saveData.highScore);
}

void GameSaveManager::SaveGame()
{
	GameSave saveData;
	saveData.highScore = m_gameInstance->m_gameState.m_state.highScore;
	FILE* fout = fopen("Resources/GameSaves/GameSave.pacman", "w");
	fwrite(&saveData, sizeof(GameSave), 1, fout);
	fclose(fout);
}
