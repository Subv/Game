#ifndef UTILS_H
#define UTILS_H

#include <limits>
#include <vector>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace Utils
{
    enum ComparisonResult
    {
        COMPARE_EQUAL,
        COMPARE_DIFFERENT,
        COMPARE_LESS_THAN,
        COMPARE_GREATER_THAN
    };

    ComparisonResult CompareFloats(float x, float y, double epsilon = std::numeric_limits<double>::epsilon());
    bool LinesIntersect(sf::Vector3f line1, sf::Vector3f line2, sf::Vector2f& intersection);
    std::vector<std::string> Split(const std::string& input, const std::string& regex);
}
#endif