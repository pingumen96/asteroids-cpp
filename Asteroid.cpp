#include "Asteroid.h"
#include "Utilities.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

constexpr float PI = 3.14159265f;

Asteroid::Asteroid(float radius) {
	// set the number of vertices between 6 and 12 to create a random shape
	int pointsCount = 6 + rand() % 7;
	shape.setPointCount(pointsCount);

	// rotation between -50 and 50 degrees per second
	rotationSpeed = -50 + rand() % 101;


	for (int i = 0; i < pointsCount; i++) {
		float angle = (i * 2 * PI) / pointsCount;

		float offset = (rand() % 20 - 10) / 50.0f; // random variation of the radius
		float distanceFromCenter = radius + radius * offset;

		// calculate the position of the vertex
		float x = std::cos(angle) * distanceFromCenter;
		float y = std::sin(angle) * distanceFromCenter;

		shape.setPoint(i, sf::Vector2f(x, y));
	}

	sf::Color randomColor = getRandomColor();

	shape.setFillColor(randomColor);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::White);

	setOriginToCenter();

	// Generate the position of the asteroid at the edges of the screen
	sf::Vector2u screenSize = sf::Vector2u(800, 600);
	float x = static_cast<float>(rand() % screenSize.x);
	float y = static_cast<float>(rand() % screenSize.y);

	if (rand() % 2 == 0) {
		if (rand() % 2 == 0)
			x = 0;
		else
			x = screenSize.x;
	} else {
		if (rand() % 2 == 0)
			y = 0;
		else
			y = screenSize.y;
	}

	shape.setPosition(x, y);

	float angle = (rand() % 360) * PI / 180.0f;
	float speed = 50.0f + rand() % 50;
	velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;
}

sf::Color Asteroid::getRandomColor() const {
	int r = rand() % 256;
	int g = rand() % 256;
	int b = rand() % 256;
	return sf::Color(r, g, b);
}

void Asteroid::update(float deltaTime) {
	shape.move(velocity * deltaTime);
	shape.rotate(rotationSpeed * deltaTime);
	wrapScreen();
}

void Asteroid::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

sf::FloatRect Asteroid::getBounds() const {
	return shape.getGlobalBounds();
}


void Asteroid::setOriginToCenter() {
	// Calcola il centro geometrico della forma basato sui vertici
	sf::Vector2f centroid(0.f, 0.f);
	for (size_t i = 0; i < shape.getPointCount(); ++i) {
		centroid += shape.getPoint(i);
	}
	centroid /= static_cast<float>(shape.getPointCount());  // Media dei vertici

	// Imposta l'origine al centro calcolato
	shape.setOrigin(centroid);
}


void Asteroid::wrapScreen() {
	sf::Vector2f position = shape.getPosition();
	sf::Vector2u screenSize = sf::Vector2u(800, 600);

	if (position.x < 0)
		position.x = screenSize.x;
	if (position.x > screenSize.x)
		position.x = 0;
	if (position.y < 0)
		position.y = screenSize.y;
	if (position.y > screenSize.y)
		position.y = 0;

	shape.setPosition(position);
}

void Asteroid::collide(GameObject& other) {
	// Gestiamo la collisione tra Asteroid e Bullet
	if (other.getType() == ObjectType::Bullet) {
		if (other.getShapeType() == ShapeType::Circle) {
			if (Utilities::checkCollision(shape, dynamic_cast<sf::CircleShape&>(other.getShape()))) {
				setActive(false);
				other.setActive(false);
			}
		}
	}
}
