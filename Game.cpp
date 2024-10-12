#include "Game.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include <algorithm>
#include <iostream>

Game::Game()
    : window(sf::VideoMode(800, 600), "Asteroids Clone")
{
    window.setFramerateLimit(60);

    // Crea il giocatore e aggiungilo a gameObjects
    auto player = std::make_unique<Player>();
    gameObjects.push_back(std::move(player));

    // Imposta il punteggio iniziale nella UI
    gameUI.setScore(score);
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime)
{
    spawnTimer += deltaTime;
    if (spawnTimer >= 2.0f) {
        auto asteroid = std::make_unique<Asteroid>();
        gameObjects.push_back(std::move(asteroid));
        spawnTimer = 0.0f;
    }

    std::vector<std::unique_ptr<GameObject>> newObjects;
    for (auto& obj : gameObjects) {
        obj->update(deltaTime);

        auto newObjs = obj->collectNewObjects();
        for (auto& newObj : newObjs) {
            newObjects.push_back(std::move(newObj));
        }
    }

    for (auto& newObj : newObjects) {
        gameObjects.push_back(std::move(newObj));
    }

    handleCollisions();

    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::unique_ptr<GameObject>& obj) {
                return !obj->isActive();
            }),
        gameObjects.end());
}

void Game::handleCollisions()
{
    for (size_t i = 0; i < gameObjects.size(); ++i) {
        for (size_t j = i + 1; j < gameObjects.size(); ++j) {
            auto& objA = gameObjects[i];
            auto& objB = gameObjects[j];

            if (objA->getBounds().intersects(objB->getBounds())) {
                auto typeA = objA->getType();
                auto typeB = objB->getType();

                if ((typeA == GameObject::ObjectType::Bullet && typeB == GameObject::ObjectType::Asteroid) || (typeA == GameObject::ObjectType::Asteroid && typeB == GameObject::ObjectType::Bullet)) {
                    objA->setActive(false);
                    objB->setActive(false);

                    // Aumenta il punteggio
                    score += 10;
                    gameUI.setScore(score); // Aggiorna la UI con il nuovo punteggio
                } else if ((typeA == GameObject::ObjectType::Player && typeB == GameObject::ObjectType::Asteroid) || (typeA == GameObject::ObjectType::Asteroid && typeB == GameObject::ObjectType::Player)) {
                    std::cout << "Hai perso!" << std::endl;
                    window.close();
                    return;
                }
            }
        }
    }
}

void Game::render()
{
    window.clear();
    for (const auto& obj : gameObjects) {
        obj->draw(window);
    }

    gameUI.draw(window); // Disegna la UI
    window.display();
}
