#ifndef POINT_H
#define POINT_H

#include "shape.h"

class Point : public Shape
{
public:
    Point();
    void paint(QPainter &painter);
};

#endif // POINT_H
