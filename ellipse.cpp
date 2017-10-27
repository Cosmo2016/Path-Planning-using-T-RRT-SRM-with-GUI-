#include "ellipse.h"

Ellipse::Ellipse()
{

}

void Ellipse::paint(QPainter &painter)
{
    painter.setBrush(this->getQBursh());
    painter.setPen(this->getQPen());
    painter.drawEllipse(start.x(), start.y(), 10, 10);
}
