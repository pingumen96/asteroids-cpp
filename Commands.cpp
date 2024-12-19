#include "Commands.h"
#include "Player.h"
#include "Bullet.h"
#include <cmath>
#include <numbers>

constexpr float PI = std::numbers::pi_v<float>;

void RotateLeftCommand::execute(Player& player, float deltaTime) {
    player.getShape().rotate(-200 * deltaTime);
}

void RotateRightCommand::execute(Player& player, float deltaTime) {
    player.getShape().rotate(200 * deltaTime);
}

void MoveForwardCommand::execute(Player& player, float deltaTime) {
    float angleRad = (player.getShape().getRotation() - 90) * PI / 180.0f;
    sf::Vector2f direction(std::cos(angleRad), std::sin(angleRad));
    player.getVelocity() += direction * player.getAcceleration() * deltaTime;
}

void ShootCommand::execute(Player& player, float deltaTime) {
    if (player.getShootCooldown() <= 0.0f) {
        auto bullet = std::make_unique<Bullet>(player.getShape().getPosition(), player.getShape().getRotation());
        player.addNewObject(std::move(bullet));
        player.resetShootCooldown();
        player.playShootSound();
    }
}
