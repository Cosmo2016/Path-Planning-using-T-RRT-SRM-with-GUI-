#ifndef POINT_H
#define POINT_H

#include "shape.h"

class MyPoint : public Shape
{
public:
    MyPoint();
    void paint(QPaintDevice* qWidget) override;
};

#endif // POINT_H
