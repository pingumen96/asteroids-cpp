#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class GameObject {
public:
	enum class ObjectType { Player, Bullet, Asteroid, };
	enum class ShapeType { Circle, Convex, };

	virtual ~GameObject() = default;

	// virtual methods to be implemented by derived classes
	virtual void update(float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) const = 0;

	// collision detection
	virtual sf::FloatRect getBounds() const = 0;
	virtual ShapeType getShapeType() const = 0;
	virtual sf::Shape& getShape() = 0;

	// object type to identify the derived class

	virtual ObjectType getType() const = 0;
	virtual void collide(GameObject& otherObject) = 0;

	// state management
	void setActive(bool active) { this->active = active; }
	bool isActive() const { return active; }

	// to collect new objects created by the object (e.g. bullets)
	virtual std::vector<std::unique_ptr<GameObject>> collectNewObjects() {
		return {};
	}

protected:
	bool active = true;
};
