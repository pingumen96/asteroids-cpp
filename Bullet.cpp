#include "Bullet.h"
#include <cmath>

constexpr float PI = 3.14159265f;

Bullet::Bullet(const sf::Vector2f& position, float rotation)
{
    shape.setRadius(2);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(position);

    // Correggi l'angolo sottraendo 90 gradi
    float angle = (rotation - 90) * PI / 180.0f;
    float speed = 400.0f;
    velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;
}

void Bullet::update(float deltaTime)
{
    shape.move(velocity * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Bullet::getPosition() const
{
    return shape.getPosition();
}
