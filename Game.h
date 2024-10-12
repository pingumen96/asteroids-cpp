#pragma once

#include "GameObject.h"
#include "GameUI.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "MusicManager.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

	// logic methods
    void handleMusic();
	void spawnAsteroids(float deltaTime);
	void updateGameObjects(float deltaTime);
    void handleCollisions();
	void checkGameOver();

    sf::RenderWindow window;

	Player* player = nullptr;
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    MusicManager musicManager;

    float spawnTimer = 0.0f;
    int score = 0;

    GameUI gameUI;
};
