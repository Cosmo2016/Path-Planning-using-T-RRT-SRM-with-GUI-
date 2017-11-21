#include "line.h"

Line::Line()
{

}

void Line::paint(QPaintDevice* qWidget)
{
    QPainter qPainter(qWidget);
    qPainter.setBrush(this->getQBursh());
    qPainter.setPen(this->getQPen());
    qPainter.drawLine(this->aPoint_, this->bPoint_);
}
