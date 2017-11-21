#include "ellipse.h"

Ellipse::Ellipse()
{

}

void Ellipse::paint(QPaintDevice *qWidget)
{
    QPainter painter(qWidget);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));
    painter.drawEllipse(aPoint_, 5, 5);
}

