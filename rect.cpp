#include "rect.h"

Rect::Rect()
{

}

void Rect::paint(QPainter &painter)
{
    painter.setBrush(this->getQBursh());
    painter.setPen(this->getQPen());
    painter.drawRect(start.x(), start.y(),
                     end.x() - start.x(), end.y() - start.y());
}
