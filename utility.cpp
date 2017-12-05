#include "utility.h"

#include <cmath>
#include <iostream>
#include <random>

float Utility::distanceBetween2Points(const float x1, const float y1,
                                             const float x2, const float y2)
{
    return sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
}

float Utility::pointAngleWithXAxis(float x, float y)
{
    float cv = atan(y / x);
    return (180 * cv) / M_PI;
}

float Utility::getIncludedAngle(float x1, float y1, float x2, float y2)
{
    float cv = atan( (y2 - y1) / (x2 - x1));
    float angle = (180 * cv) / M_PI;
    if (x2 < x1 && y2 > y1) {
        angle = 180 + angle;
    }
    if (x2 < x1 && y2 < y1) {
        angle = 180 + angle;
    }
    if (x2 > x1 && y2 < y1) {
        angle = 360 + angle;
    }
    return angle;
}

float Utility::randomProbability()
{
    return randomRangeNumber(0, 1000) / 1000.0;
}

int Utility::randomRangeNumber(int start, int end)
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<> dis(start, end);
    auto dice = std::bind(dis, engine);
    return dice();
}
