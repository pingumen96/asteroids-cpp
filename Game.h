#pragma once

#include "GameObject.h"
#include "GameUI.h"
#include "Player.h"
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

	void checkGameOver();

    sf::RenderWindow window;

	Player* player = nullptr;
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    float spawnTimer = 0.0f;
    int score = 0;

    GameUI gameUI;
};
