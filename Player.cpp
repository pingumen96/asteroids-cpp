#include "Player.h"
#include "Bullet.h"
#include "Utilities.h"
#include "Command.h"
#include <cmath>
#include <numbers>

constexpr float PI = std::numbers::pi_v<float>;

Player::Player() {
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(0, -20));
	shape.setPoint(1, sf::Vector2f(-15, 15));
	shape.setPoint(2, sf::Vector2f(15, 15));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(400, 300);

	if (!shootBuffer.loadFromFile("res/shoot.wav")) {
		throw std::runtime_error("Cannot load sound file");
	}
	shootSound.setBuffer(shootBuffer);

	keyBindings[sf::Keyboard::Left] = std::make_unique<RotateLeftCommand>();
	keyBindings[sf::Keyboard::Right] = std::make_unique<RotateRightCommand>();
	keyBindings[sf::Keyboard::Up] = std::make_unique<MoveForwardCommand>();
	keyBindings[sf::Keyboard::Space] = std::make_unique<ShootCommand>();
}

void Player::update(float deltaTime) {
	for (const auto& [key, command] : keyBindings) {
		if (sf::Keyboard::isKeyPressed(key)) {
			command->execute(*this, deltaTime);
		}
	}

	// Riduzione velocità (damping)
	velocity *= damping;

	// Muovi l'astronave
	shape.move(velocity * deltaTime);

	// Cooldown
	if (shootCooldown > 0.0f) {
		shootCooldown -= deltaTime;
	}

	wrapScreen();
}


void Player::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

std::vector<std::unique_ptr<GameObject>> Player::collectNewObjects() {
	std::vector<std::unique_ptr<GameObject>> objects;
	objects.swap(newObjects);
	return objects;
}

sf::FloatRect Player::getBounds() const {
	return shape.getGlobalBounds();
}

void Player::collide(GameObject& other) {
	if (other.getType() == ObjectType::Asteroid) {
		if (other.getShapeType() == ShapeType::Convex) {
			if (Utilities::checkCollision(dynamic_cast<sf::ConvexShape&>(other.getShape()), shape)) {
				setActive(false);
				other.setActive(false);
			}
		}
	}
}

void Player::wrapScreen() {
	sf::Vector2f position = shape.getPosition();
	if (position.x < 0)
		position.x = 800;
	if (position.x > 800)
		position.x = 0;
	if (position.y < 0)
		position.y = 600;
	if (position.y > 600)
		position.y = 0;
	shape.setPosition(position);
}
