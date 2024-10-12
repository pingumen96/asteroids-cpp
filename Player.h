#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Player : public GameObject {
public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    ObjectType getType() const override { return ObjectType::Player; }

    // Sovrascrivi il metodo per raccogliere nuovi oggetti (proiettili sparati)
    std::vector<std::unique_ptr<GameObject>> collectNewObjects() override;

private:
    void wrapScreen();

    sf::ConvexShape shape;
    sf::Vector2f velocity;

    const float acceleration = 400.0f;
    const float damping = 0.99f;

    // Cooldown per lo sparo
    float shootCooldown = 0.0f;
    const float shootCooldownDuration = 0.5f;

    // Contenitore per nuovi oggetti creati (proiettili)
    std::vector<std::unique_ptr<GameObject>> newObjects;
};
