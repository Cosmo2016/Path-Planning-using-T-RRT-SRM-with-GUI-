#include "human.h"
#include <random>
#include <cmath>
#include <utility.h>

Human::Human()
{
    this->id = Utility::randomRangeNumber(
                0, pow(2, sizeof(int) * 8 - 1) - 1);
    this->setDirection(0);
    this->velocity_ = 0;
}

Human::~Human()
{

}

void Human::setDirection(float angle)
{
    if (angle >= 0 && angle <= 360) {
        this->direction_ = angle - 90;
    } else {
        // throw exception
    }
}

double Human::getDirection() const
{
    return this->direction_ + 90;
}

int Human::getHumanId() const
{
    return this->id;
}

void Human::paint(QPaintDevice *qWidget)
{
    QPainter painter(qWidget);

    const int ellipseWidth = 50;
    const int ellipseHeight = 20;

    painter.save();

    painter.translate(QPointF(aPoint_.x(), aPoint_.y()));

    // 反走样
    // painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));

    painter.rotate(this->direction_);

    // Notice: It has a central point adjustment.
    float ellipse_central_x = -ellipseWidth / 2.0;
    float ellipse_central_y = -ellipseHeight / 2.0;
    painter.drawEllipse(ellipse_central_x, ellipse_central_y,
                        ellipseWidth, ellipseHeight);

    // Direction
    painter.setPen(QPen(Qt::blue));
    painter.drawLine(QPoint(0, 0), QPoint(0, 10));

    painter.restore();

    painter.setPen(QPen(Qt::blue));
    painter.drawEllipse(aPoint_, 10, 10);

    if(isGuidelineVisiable) {
        painter.setPen(QPen(Qt::yellow));
        painter.drawEllipse(aPoint_, maxDistants_, maxDistants_);
        painter.drawEllipse(aPoint_, minDistants_, minDistants_);
    }

}
