#include "Game.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include "Utilities.h"
#include <algorithm>
#include <iostream>

Game::Game()
    : window(sf::VideoMode(800, 600), "Asteroids Clone") {
    window.setFramerateLimit(60);

    // music manager
    if (!musicManager.loadMusic("res/normal_music.ogg", "res/intense_music.ogg")) {
        std::cerr << "Failed to load music" << std::endl;
    }

    musicManager.playNormal();

    // create player and add it to the game objects
    auto playerObject = std::make_unique<Player>();
    player = playerObject.get();
    gameObjects.push_back(std::move(playerObject));

    // set starting score in the UI
    gameUI.setScore(score);
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    spawnAsteroids(deltaTime);
    updateGameObjects(deltaTime);
    handleMusic();
    handleCollisions();
    checkGameOver();

	// remove inactive objects
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::unique_ptr<GameObject>& obj) {
                return !obj->isActive();
            }),
        gameObjects.end());
}

void Game::spawnAsteroids(float deltaTime) {
    spawnTimer += deltaTime;
    if (spawnTimer >= 2.0f) {
        auto asteroid = std::make_unique<Asteroid>();
        gameObjects.push_back(std::move(asteroid));
        spawnTimer = 0.0f;
    }
}

void Game::updateGameObjects(float deltaTime) {
    std::vector<std::unique_ptr<GameObject>> newObjects;
    for (auto& obj : gameObjects) {
        obj->update(deltaTime);

        // Aggiungi nuovi oggetti (es. proiettili)
        auto newObjs = obj->collectNewObjects();
        for (auto& newObj : newObjs) {
            newObjects.push_back(std::move(newObj));
        }
    }

	// add new objects to the game
    for (auto& newObj : newObjects) {
        gameObjects.push_back(std::move(newObj));
    }
}

void Game::handleMusic() {
    int asteroidCount = std::count_if(gameObjects.begin(), gameObjects.end(),
        [](const std::unique_ptr<GameObject>& obj) {
            return obj->getType() == GameObject::ObjectType::Asteroid;
        });

	// change music based on asteroid count
    if (asteroidCount > 10) {
        musicManager.playIntense();
    } else {
        musicManager.playNormal();
    }
}

void Game::handleCollisions() {
    for (size_t i = 0; i < gameObjects.size(); ++i) {
        for (size_t j = i + 1; j < gameObjects.size(); ++j) {
            auto& objA = gameObjects[i];
            auto& objB = gameObjects[j];

            objA->collide(*objB);
            objB->collide(*objA);
        }
    }
}

void Game::checkGameOver() {
    if (!player->isActive()) {
        std::cout << "Game Over! Il giocatore è stato distrutto." << std::endl;
        window.close();
    }
}

void Game::render() {
    window.clear();
    for (const auto& obj : gameObjects) {
        obj->draw(window);
    }

    gameUI.draw(window);
    window.display();
}
