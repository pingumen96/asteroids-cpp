#include "Bullet.h"
#include "Utilities.h"
#include <cmath>

constexpr float PI = 3.14159265f;

Bullet::Bullet(const sf::Vector2f& position, float rotation) {
	shape.setRadius(2);
	shape.setFillColor(sf::Color::White);
	shape.setPosition(position);

	// correct the angle to point upwards
	float angle = (rotation - 90) * PI / 180.0f;
	float speed = 400.0f;
	velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;
}

void Bullet::update(float deltaTime) {
	shape.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const {
	return shape.getGlobalBounds();
}

void Bullet::collide(GameObject& other) {
	if (other.getType() == ObjectType::Asteroid) {
		if (other.getShapeType() == ShapeType::Convex) {
			if (Utilities::checkCollision(dynamic_cast<sf::ConvexShape&>(other.getShape()), shape)) {
				setActive(false);
				other.setActive(false);
			}
		}
	}
}
