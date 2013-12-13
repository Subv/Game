#ifndef UTILS_H
#define UTILS_H
#include <limits>
#include <vector>
#include <string>

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
    std::vector<std::string> Split(const std::string& input, const std::string& regex);
}
#endif