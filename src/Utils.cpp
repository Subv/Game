#include "Utils.h"
#include <cmath>
#include <limits>

namespace Utils
{
    Utils::ComparisonResult CompareFloats(float x, float y)
    {
        if (std::fabs(x - y) < std::numeric_limits<double>::epsilon())
            return COMPARE_EQUAL;
        else if (x > y + std::numeric_limits<double>::epsilon())
            return COMPARE_GREATER_THAN;
        else if (y > x + std::numeric_limits<double>::epsilon())
            return COMPARE_LESS_THAN;
        
        return COMPARE_DIFFERENT;
    }
}