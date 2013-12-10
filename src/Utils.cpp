#include "Utils.h"
#include "SharedDefines.h"
#include <cmath>
#include <limits>

namespace Common
{
    const int DefaultHealthPoints = 100;
    const float GravityAcceleration = 40.f;

    const float TerminalVerticalSpeed = 160.f;
    const float TerminalHorizontalSpeed = 160.f;

    const float HorizontalBrakeAcceleration = 15.f;
    const float HorizontalMoveAcceleration = 15.f;

    const float JumpVelocity = 100.f;
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
}