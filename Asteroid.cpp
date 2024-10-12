#include "Asteroid.h"
#include <cmath>
#include <cstdlib>

constexpr float PI = 3.14159265f;

Asteroid::Asteroid(float radius) {
	shape.setRadius(radius);
	shape.setPointCount(8);

	sf::Color randomColor = getRandomColor();

	shape.setFillColor(randomColor);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::White);
	shape.setOrigin(radius, radius);

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
	wrapScreen();
}

void Asteroid::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

sf::FloatRect Asteroid::getBounds() const {
	return shape.getGlobalBounds();
}

sf::Vector2f Asteroid::getPosition() const {
	return shape.getPosition();
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
