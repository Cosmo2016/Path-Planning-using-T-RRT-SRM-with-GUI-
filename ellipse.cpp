#include "ellipse.h"

Ellipse::Ellipse()
{

}

void Ellipse::paint(QPaintDevice *qWidget)
{
    QPainter painter(qWidget);
    painter.setBrush(this->getQBursh());
    painter.setPen(this->getQPen());
    painter.drawEllipse(aPoint_, 5, 5);
}

