#include "point.h"

Point::Point()
{
}

void Point::paint(QPaintDevice* qWidget)
{
    QPainter painter(qWidget);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));
    painter.drawPoint(aPoint_.x(), aPoint_.y());
}
