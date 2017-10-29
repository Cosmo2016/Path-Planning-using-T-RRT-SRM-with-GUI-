#include "point.h"

Point::Point()
{

}

void Point::paint(QPainter &painter)
{
    painter.setBrush(this->getQBursh());
    painter.setPen(this->getQPen());
    painter.drawPoint(startPoint_.x(), startPoint_.y());
}
