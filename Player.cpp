#include "Player.h"
#include "Bullet.h"
#include <cmath>
#include <numbers>

constexpr float PI = std::numbers::pi_v<float>;

Player::Player()
{
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0, -20));
    shape.setPoint(1, sf::Vector2f(-15, 15));
    shape.setPoint(2, sf::Vector2f(15, 15));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(400, 300);
}

void Player::update(float deltaTime)
{
    // Gestisci la rotazione
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        shape.rotate(-200 * deltaTime);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        shape.rotate(200 * deltaTime);

    // Movimento in avanti
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        float angleRad = (shape.getRotation() - 90) * PI / 180.0f;
        sf::Vector2f direction(std::cos(angleRad), std::sin(angleRad));
        velocity += direction * acceleration * deltaTime;
    }

    // Riduzione della velocità (inerzia)
    velocity *= damping;

    // Muovi la nave
    shape.move(velocity * deltaTime);

    // Aggiorna il cooldown dello sparo
    if (shootCooldown > 0.0f) {
        shootCooldown -= deltaTime;
    }

    // Sparo (solo se il cooldown è scaduto)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootCooldown <= 0.0f) {
        auto bullet = std::make_unique<Bullet>(shape.getPosition(), shape.getRotation());
        newObjects.push_back(std::move(bullet));
        shootCooldown = shootCooldownDuration; // Reset del cooldown dopo lo sparo
    }

    // Gestione del wrapping dello schermo
    wrapScreen();
}

void Player::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}

sf::FloatRect Player::getBounds() const
{
    return shape.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const
{
    return shape.getPosition();
}

std::vector<std::unique_ptr<GameObject>> Player::collectNewObjects()
{
    std::vector<std::unique_ptr<GameObject>> objects;
    objects.swap(newObjects); // Scambia i contenuti dei vettori
    return objects;
}

void Player::wrapScreen()
{
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
