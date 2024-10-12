#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Bullet : public GameObject {
public:
    Bullet(const sf::Vector2f& position, float rotation);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    ObjectType getType() const override { return ObjectType::Bullet; }

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};
