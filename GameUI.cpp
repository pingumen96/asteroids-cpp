#include "GameUI.h"

GameUI::GameUI() {
    if (!font.loadFromFile("res/Atari.ttf")) {
		throw std::runtime_error("Cannot load font");
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 10); // position in the top-left corner
}

void GameUI::setScore(int newScore) {    
    score = newScore;
	scoreText.setString("Score: " + std::to_string(score)); // update the score text
}

void GameUI::draw(sf::RenderWindow& window) {
    window.draw(scoreText);
}
