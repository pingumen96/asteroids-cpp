#pragma once

#include <SFML/Graphics.hpp>

class GameUI {
public:
    GameUI();

    void setScore(int score);

    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text scoreText;
    int score = 0;
};
