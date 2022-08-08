#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Game;

class ScoreBoard {
public:
	ScoreBoard(Game* gameInstance);
	~ScoreBoard();

	void Draw();
	void SetCurrentScore(uint score);
	void SetHighScore(uint highScore);
	sf::Text m_currentScoreText;
	sf::Text m_highScoreText;
	sf::Font m_font;
	Game* m_gameInstance;
private:

};

#endif
