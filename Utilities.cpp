#include "Utilities.h"
#include <cmath>
#include <vector>

namespace {
    void projectShapeOntoAxis(const std::vector<sf::Vector2f>& points, const sf::Vector2f& axis, float& min, float& max) {
		// project the first point onto the axis
        float dotProduct = points[0].x * axis.x + points[0].y * axis.y;
        min = max = dotProduct;

		// project the rest of the points
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


bool Utilities::checkCollision(const sf::CircleShape& shape1, const sf::CircleShape& shape2) {
    sf::Vector2f pos1 = shape1.getPosition();
    sf::Vector2f pos2 = shape2.getPosition();
    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
    return distance < shape1.getRadius() + shape2.getRadius();
}

bool Utilities::checkCollision(const sf::ConvexShape& shape1, const sf::CircleShape& shape2) {
	// simplified collision check, distance between the center of the circle and the center of the shape
    sf::Vector2f pos1 = shape1.getPosition();
    sf::Vector2f pos2 = shape2.getPosition();
    float distance = std::sqrt(std::pow(pos1.x - pos2.x, 2) + std::pow(pos1.y - pos2.y, 2));
    return distance < 20.0f + shape2.getRadius();
}

bool Utilities::checkCollision(const sf::ConvexShape& shape1, const sf::ConvexShape& shape2) {
	// get the number of points in each shape
    size_t count1 = shape1.getPointCount();
    size_t count2 = shape2.getPointCount();

	// get the transformed points (in world space) of shape1
    std::vector<sf::Vector2f> points1(count1);
    for (size_t i = 0; i < count1; ++i) {
        points1[i] = shape1.getTransform().transformPoint(shape1.getPoint(i));
    }

	// get the transformed points (in world space) of shape2
    std::vector<sf::Vector2f> points2(count2);
    for (size_t i = 0; i < count2; ++i) {
        points2[i] = shape2.getTransform().transformPoint(shape2.getPoint(i));
    }

	// check the separating axis theorem
    for (size_t i = 0; i < count1; ++i) {
        size_t next = (i + 1) % count1;
        sf::Vector2f edge = points1[next] - points1[i];
		sf::Vector2f axis(-edge.y, edge.x); // perpendicular axis

		// normalize the axis
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        axis /= length;

		// project both shapes onto the axis
        float minA, maxA, minB, maxB;
        projectShapeOntoAxis(points1, axis, minA, maxA);
        projectShapeOntoAxis(points2, axis, minB, maxB);

		// if there is no overlap, there is no collision
        if (maxA < minB || maxB < minA) {
			return false; // separating axis found
        }
    }

	// check the other set of edges
    for (size_t i = 0; i < count2; ++i) {
        size_t next = (i + 1) % count2;
        sf::Vector2f edge = points2[next] - points2[i];
		sf::Vector2f axis(-edge.y, edge.x); // perpendicular axis

		// normalize the axis
        float length = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        axis /= length;

		// project both shapes onto the axis
        float minA, maxA, minB, maxB;
        projectShapeOntoAxis(points1, axis, minA, maxA);
        projectShapeOntoAxis(points2, axis, minB, maxB);

		// if there is no overlap, there is no collision
        if (maxA < minB || maxB < minA) {
			return false; // found a separating axis
        }
    }

	// no separating axis found, the shapes are colliding
    return true;
}
