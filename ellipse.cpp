#include "ellipse.h"

Ellipse::Ellipse()
{

}

void Ellipse::paint(QPainter &painter)
{
    painter.setBrush(this->getQBursh());
    painter.setPen(this->getQPen());
    painter.drawEllipse(startPoint_, 5, 5);
}
