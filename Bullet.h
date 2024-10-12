#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Bullet : public GameObject {
public:
    Bullet(const sf::Vector2f& position, float rotation);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    sf::FloatRect getBounds() const override;
    sf::Shape& getShape() override { return shape; }
	ShapeType getShapeType() const override { return ShapeType::Circle; }
    ObjectType getType() const override { return ObjectType::Bullet; }

    void collide(GameObject& other) override;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};
