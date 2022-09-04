// Copyright © Veselin Dafchev 2022 All Rights Reserved.
#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"

class Game;

class ScoreBoard {
public:
	ScoreBoard(Game* gameInstance);
	~ScoreBoard();

	void Draw();
	void SetCurrentScore(uint32_t score);
	void SetHighScore(uint32_t highScore);
	
private:
	sf::Text m_currentScoreText;
	sf::Text m_highScoreText;
	sf::Font m_font;
	Game* m_gameInstance;
};
