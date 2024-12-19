#pragma once

#include "GameObject.h"
#include "Commands.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <unordered_map>
#include <vector>

class Player : public GameObject {
public:
    Player();

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

	sf::FloatRect getBounds() const override;
	sf::Shape& getShape() override { return shape; }
    ShapeType getShapeType() const override { return ShapeType::Convex; }
    ObjectType getType() const override { return ObjectType::Player; }

	// override the method to collect new objects (bullets)
    std::vector<std::unique_ptr<GameObject>> collectNewObjects() override;

    void collide(GameObject& other) override;

	sf::Vector2f& getVelocity() { return velocity; }
	sf::Vector2f getPosition() const { return shape.getPosition(); }
	float getAcceleration() const { return acceleration; }
	float getShootCooldown() const { return shootCooldown; }

	void addNewObject(std::unique_ptr<GameObject> object) { newObjects.push_back(std::move(object)); }
	void resetShootCooldown() { shootCooldown = shootCooldownDuration; }
	void playShootSound() { shootSound.play(); }

private:
    void wrapScreen();

    sf::ConvexShape shape;
    sf::Vector2f velocity;

    const float acceleration = 400.0f;
    const float damping = 0.99f;

    float shootCooldown = 0.0f;
    const float shootCooldownDuration = 0.5f;

    // sound management
	sf::SoundBuffer shootBuffer;
	sf::Sound shootSound;

	// new objects created by the player
    std::vector<std::unique_ptr<GameObject>> newObjects;
	std::unordered_map<sf::Keyboard::Key, std::unique_ptr<Command>> keyBindings;
};
