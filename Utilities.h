#pragma once

#include <SFML/Graphics.hpp>

namespace Utilities {
    bool checkCollision(const sf::CircleShape& shape1, const sf::CircleShape& shape2);
    bool checkCollision(const sf::ConvexShape& shape1, const sf::CircleShape& shape2);
    bool checkCollision(const sf::ConvexShape& shape1, const sf::ConvexShape& shape2);
}
