#ifndef POINT_H
#define POINT_H

#include "shape.h"

class Point : public Shape
{
public:
    Point();
    void paint(QPaintDevice* qWidget) override;
};

#endif // POINT_H
