#include "Game.h"


ScoreBoard::ScoreBoard(Game* gameInstance)
{
	m_gameInstance = gameInstance;
	if (!m_font.loadFromFile("Resources/Fonts/RetroGaming.ttf")) {
		std::cout << "ERROR TFF";
	}

	auto ConfigurateElements = [&](sf::Text& element, std::string initial_text, sf::Font& font, sf::Vector2f offset) {
		element.setString(initial_text);
		element.setCharacterSize(24);
		element.setFillColor(sf::Color::White);
		element.setFont(font);
		element.setPosition(element.getPosition() + offset);
	};

	ConfigurateElements(m_currentScoreText,"SCORE 0",m_font,{ 150.0, 0.0 });
	ConfigurateElements(m_highScoreText, "HIGH 0", m_font, { 550.0, 0.0 });

}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Draw()
{
	m_gameInstance->GetScreen().draw(m_currentScoreText);
	m_gameInstance->GetScreen().draw(m_highScoreText);
}

void ScoreBoard::SetCurrentScore(uint32_t score)
{
	m_currentScoreText.setString("SCORE " + std::to_string(score));
}

void ScoreBoard::SetHighScore(uint32_t highScore)
{
	m_highScoreText.setString("HIGH " + std::to_string(highScore));
}
