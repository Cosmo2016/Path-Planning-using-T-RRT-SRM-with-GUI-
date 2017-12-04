#ifndef UTILITY_H
#define UTILITY_H


class Utility
{
public:
    static float distanceBetween2Points(const float x1, const float y1,
                                        const float x2, const float y2);

    static float pointAngleWithXAxis(float x, float y);

    static float pointAngleXxxxxxxx(float x1, float y1, float x2, float y2);

    static float randomProbability();

    static int randomRangeNumber(int start, int end);
};

#endif // UTILITY_H
