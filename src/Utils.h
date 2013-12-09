#ifndef UTILS_H
#define UTILS_H

namespace Utils
{
    enum ComparisonResult
    {
        COMPARE_EQUAL,
        COMPARE_DIFFERENT,
        COMPARE_LESS_THAN,
        COMPARE_GREATER_THAN
    };
    ComparisonResult CompareFloats(float x, float y);
}
#endif