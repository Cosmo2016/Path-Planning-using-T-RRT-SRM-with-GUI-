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

float Utility::randomProbability()
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<> dis(0, 1000);
    auto dice = std::bind(dis, engine);
    return dice() / 1000.0;
}

