#include "Utils.h"
#include "SharedDefines.h"
#include "ResourceManager.h"
#include <cmath>
#include <vector>
#include <string>
#include <regex>
#include <limits>
#include <iostream>

namespace Common
{
    const std::string KeyBindingsFile = sResourceManager->ResourcesDir + "Bindings.bnd";

    const unsigned int NumPlayers = 2;
    const unsigned int MaxPlayers = 5;

    const int DefaultHealthPoints = 100;
    const float GravityAcceleration = 500.f;

    const float TerminalVerticalSpeed = 1060.f;
    const float TerminalHorizontalSpeed = 3000.f;

    const float HorizontalBrakeAcceleration = 15.f;
    const float HorizontalMoveSpeed = 300.f;

    const float JumpVelocity = 400.f;
}

namespace Utils
{
    Utils::ComparisonResult CompareFloats(float x, float y, double epsilon)
    {
        if (std::fabs(x - y) < epsilon)
            return COMPARE_EQUAL;
        else if (x > y + epsilon)
            return COMPARE_GREATER_THAN;
        else if (y > x + epsilon)
            return COMPARE_LESS_THAN;
        
        return COMPARE_DIFFERENT;
    }

    // Pass the lines in the form Ax + By = C as (A, B, C) in the vector
    bool LinesIntersect(sf::Vector3f line1, sf::Vector3f line2, sf::Vector2f& intersection)
    {
        float delta = line1.x * line2.y - line2.x * line1.y;
        
        if (CompareFloats(delta, 0.f) == COMPARE_EQUAL)
            return false;

        intersection.x = (line2.y * line1.z - line1.y * line2.z) / delta;
        intersection.y = (line1.x * line2.z - line2.x * line1.z) / delta;
        return true;
    }

    std::vector<std::string> Split(const std::string& input, const std::string& regex)
    {
        std::regex ws_re(regex); // whitespace
        std::vector<std::string> out;
        std::copy(std::sregex_token_iterator(input.begin(), input.end(), ws_re, -1),
            std::sregex_token_iterator(),
            std::back_inserter(out));
        return out;
    }
}