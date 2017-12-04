#include "mypoint.h"

MyPoint::MyPoint()
{
}

void MyPoint::paint(QPaintDevice* qWidget)
{
    QPainter painter(qWidget);
    // painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));
    painter.drawPoint(aPoint_.x(), aPoint_.y());
}
