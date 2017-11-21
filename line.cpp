#include "line.h"

Line::Line()
{

}

void Line::paint(QPaintDevice* qWidget)
{
    QPainter qPainter(qWidget);
    qPainter.setBrush(QBrush(this->getQBurshColor()));
    qPainter.setPen(QPen(this->getQPenColor()));
    qPainter.drawLine(this->aPoint_, this->bPoint_);
}
