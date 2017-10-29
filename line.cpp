#include "line.h"

Line::Line()
{

}

void Line::paint(QPainter &painter)
{
    painter.drawLine(this->startPoint_, this->endPoint_);
}
