#include "ellipse.h"

Ellipse::Ellipse()
{

}

void Ellipse::paint(QPainter &painter)
{
    painter.drawEllipse(start.x(), start.y(), 10, 10);
}
