#include "rect.h"

Rect::Rect()
{

}

void Rect::paint(QPaintDevice* qWidget)
{
    QPainter painter(qWidget);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));
    painter.drawRect(aPoint_.x(), aPoint_.y(),
                     bPoint_.x() - aPoint_.x(), bPoint_.y() - aPoint_.y());
}
