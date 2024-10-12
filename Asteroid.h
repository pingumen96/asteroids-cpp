#pragma once

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Asteroid : public GameObject {
public:
    Asteroid(float radius = 30.0f);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

	sf::FloatRect getBounds() const override;
	ShapeType getShapeType() const override { return ShapeType::Convex; }
    sf::Shape& getShape() override { return shape; }

    ObjectType getType() const override { return ObjectType::Asteroid; }
	void collide(GameObject& other) override;

private:
    void wrapScreen();
	sf::Color getRandomColor() const;
	void setOriginToCenter();

    sf::ConvexShape shape;
    sf::Vector2f velocity;
	float rotationSpeed;
};
