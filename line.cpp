#include "line.h"

Line::Line()
{

}

void Line::paint(QPainter &painter)
{
    painter.drawLine(this->aPoint_, this->bPoint_);
}
