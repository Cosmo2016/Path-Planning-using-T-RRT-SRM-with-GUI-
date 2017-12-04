#include "human.h"
#include <random>
#include <cmath>

Human::Human()
{
    this->id = generateHumanId();
}

Human::~Human()
{

}

void Human::setDirection(double angle)
{
    this->direction_ = angle;
}

double Human::getDirection() const
{
    return this->direction_;
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
    // painter.translate(aPoint_);
    // 反走样
    // painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));
    painter.rotate(10);
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

int Human::generateHumanId() const
{
    // Set seed，every time seed is different
    std::default_random_engine engine(time(nullptr));
    std::uniform_int_distribution<> dis(0, pow(2, sizeof(int) * 8 - 1) - 1);
    return dis(engine);
}
