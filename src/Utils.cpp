#include "Utils.h"
#include <cmath>
#include <limits>

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