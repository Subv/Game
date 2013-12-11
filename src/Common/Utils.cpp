#include "Utils.h"
#include "SharedDefines.h"
#include <cmath>
#include <limits>

namespace Common
{
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
}