#include "ScoreBoard.h"
#include "Game.h"


ScoreBoard::ScoreBoard(Game* gameInstance)
{
	m_gameInstance = gameInstance;
	m_currentScoreText = sf::Text();
	m_highScoreText = sf::Text();
	if (!m_font.loadFromFile("Resources/Fonts/RetroGaming.ttf")) {
		std::cout << "ERROR TFF";
	}
	m_currentScoreText.setString("SCORE "+ std::to_string(0));
	m_currentScoreText.setCharacterSize(24);
	m_currentScoreText.setFillColor(sf::Color::White);
	m_currentScoreText.setFont(m_font);
	sf::Vector2f offsetScore(150.0, 0.0);
	m_currentScoreText.setPosition(m_currentScoreText.getPosition() + offsetScore);

	m_highScoreText.setString("HIGH " + std::to_string(0));
	m_highScoreText.setCharacterSize(24);
	m_highScoreText.setFillColor(sf::Color::White);
	m_highScoreText.setFont(m_font);
	sf::Vector2f offsetHigh(550.0, 0.0);
	m_highScoreText.setPosition(m_highScoreText.getPosition() + offsetHigh);
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Draw()
{
	m_gameInstance->m_screen->draw(m_currentScoreText);
	m_gameInstance->m_screen->draw(m_highScoreText);
}

void ScoreBoard::SetCurrentScore(uint score)
{
	m_currentScoreText.setString("SCORE " + std::to_string(score));
}

void ScoreBoard::SetHighScore(uint highScore)
{
	m_highScoreText.setString("HIGH " + std::to_string(highScore));
}
