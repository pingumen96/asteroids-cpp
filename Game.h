#pragma once

#include "GameObject.h"
#include "GameUI.h" // Includi la UI
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void handleCollisions();

    sf::RenderWindow window;
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    float spawnTimer = 0.0f;
    int score = 0; // Punteggio del gioco

    GameUI gameUI; // Istanza della UI
};
