#include "rect.h"

Rect::Rect()
{

}

void Rect::paint(QPainter &painter)
{
    painter.setBrush(this->getQBursh());
    painter.setPen(this->getQPen());
    painter.drawRect(startPoint_.x(), startPoint_.y(),
                     endPoint_.x() - startPoint_.x(), endPoint_.y() - startPoint_.y());
}
