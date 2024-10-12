#include "Utilities.h"
#include <cmath>

bool Utilities::checkCollision(const sf::CircleShape& shape1, const sf::CircleShape& shape2)
{
    sf::Vector2f pos1 = shape1.getPosition();
    sf::Vector2f pos2 = shape2.getPosition();
    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
    return distance < shape1.getRadius() + shape2.getRadius();
}

bool Utilities::checkCollision(const sf::ConvexShape& shape1, const sf::CircleShape& shape2)
{
    // Controllo semplificato: distanza tra i centri
    sf::Vector2f pos1 = shape1.getPosition();
    sf::Vector2f pos2 = shape2.getPosition();
    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
    return distance < 20.0f + shape2.getRadius(); // 20.0f come approssimazione del raggio della nave
}
