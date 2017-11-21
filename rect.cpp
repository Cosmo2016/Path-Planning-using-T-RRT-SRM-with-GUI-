#include "rect.h"

Rect::Rect()
{

}

void Rect::paint(QPaintDevice* qWidget)
{
    QPainter painter(qWidget);
    painter.setBrush(this->getQBursh());
    painter.setPen(this->getQPen());
    painter.drawRect(aPoint_.x(), aPoint_.y(),
                     bPoint_.x() - aPoint_.x(), bPoint_.y() - aPoint_.y());
}
