#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Asteroid : public GameObject {
public:
    Asteroid(float radius = 30.0f);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;
    sf::Vector2f getPosition() const override;
    ObjectType getType() const override { return ObjectType::Asteroid; }

private:
    void wrapScreen();
	sf::Color getRandomColor() const;

    sf::CircleShape shape;
    sf::Vector2f velocity;
};
