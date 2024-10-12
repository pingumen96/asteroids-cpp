#include "Utilities.h"
#include <cmath>
#include <vector>

namespace {
    void projectShapeOntoAxis(const std::vector<sf::Vector2f>& points, const sf::Vector2f& axis, float& min, float& max) {
        // Proietta il primo punto
        float dotProduct = points[0].x * axis.x + points[0].y * axis.y;
        min = max = dotProduct;

        // Proietta gli altri punti
        for (size_t i = 1; i < points.size(); ++i) {
            dotProduct = points[i].x * axis.x + points[i].y * axis.y;
            if (dotProduct < min) {
                min = dotProduct;
            }
            if (dotProduct > max) {
                max = dotProduct;
            }
        }
    }
}

// Collisione tra due sf::CircleShape
bool Utilities::checkCollision(const sf::CircleShape& shape1, const sf::CircleShape& shape2) {
    sf::Vector2f pos1 = shape1.getPosition();
    sf::Vector2f pos2 = shape2.getPosition();
    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
    return distance < shape1.getRadius() + shape2.getRadius();
}

// Collisione tra sf::ConvexShape e sf::CircleShape
bool Utilities::checkCollision(const sf::ConvexShape& shape1, const sf::CircleShape& shape2) {
    // Controllo semplificato: distanza tra i centri
    sf::Vector2f pos1 = shape1.getPosition();
    sf::Vector2f pos2 = shape2.getPosition();
    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
    return distance < 20.0f + shape2.getRadius(); // 20.0f come approssimazione del raggio della nave
}

// Collisione tra due sf::ConvexShape usando il SAT
bool Utilities::checkCollision(const sf::ConvexShape& shape1, const sf::ConvexShape& shape2) {
    // Ottieni il numero di punti di ciascuna forma
    size_t count1 = shape1.getPointCount();
    size_t count2 = shape2.getPointCount();

    // Ottieni i punti trasformati (in world space) della shape1
    std::vector<sf::Vector2f> points1(count1);
    for (size_t i = 0; i < count1; ++i) {
        points1[i] = shape1.getTransform().transformPoint(shape1.getPoint(i));
    }

    // Ottieni i punti trasformati (in world space) della shape2
    std::vector<sf::Vector2f> points2(count2);
    for (size_t i = 0; i < count2; ++i) {
        points2[i] = shape2.getTransform().transformPoint(shape2.getPoint(i));
    }

    // Controlla gli assi separatori della shape1
    for (size_t i = 0; i < count1; ++i) {
        size_t next = (i + 1) % count1;
        sf::Vector2f edge = points1[next] - points1[i];
        sf::Vector2f axis(-edge.y, edge.x); // Asse perpendicolare

        // Normalizza l'asse
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        axis /= length;

        // Proietta entrambe le forme sull'asse
        float minA, maxA, minB, maxB;
        projectShapeOntoAxis(points1, axis, minA, maxA);
        projectShapeOntoAxis(points2, axis, minB, maxB);

        // Se non c'è sovrapposizione, non c'è collisione
        if (maxA < minB || maxB < minA) {
            return false; // Separating axis trovato
        }
    }

    // Controlla gli assi separatori della shape2
    for (size_t i = 0; i < count2; ++i) {
        size_t next = (i + 1) % count2;
        sf::Vector2f edge = points2[next] - points2[i];
        sf::Vector2f axis(-edge.y, edge.x); // Asse perpendicolare

        // Normalizza l'asse
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        axis /= length;

        // Proietta entrambe le forme sull'asse
        float minA, maxA, minB, maxB;
        projectShapeOntoAxis(points1, axis, minA, maxA);
        projectShapeOntoAxis(points2, axis, minB, maxB);

        // Se non c'è sovrapposizione, non c'è collisione
        if (maxA < minB || maxB < minA) {
            return false; // Separating axis trovato
        }
    }

    // Nessun asse separatore trovato, le forme collidono
    return true;
}
