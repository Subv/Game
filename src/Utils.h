#ifndef UTILS_H
#define UTILS_H
#include <limits>

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
}
#endif