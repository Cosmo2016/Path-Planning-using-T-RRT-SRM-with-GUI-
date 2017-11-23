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

    qreal cx = aPoint_.x();
    qreal cy = aPoint_.y();

    painter.save();
    painter.translate(QPointF(cx, cy));
    // painter.translate(aPoint_);
    // 反走样
    // painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));
    painter.rotate(30);
    // Notice: It has a central point adjustment.
    qreal ellipse_central_x = -ellipseWidth / 2.0;
    qreal ellipse_central_y = -ellipseHeight / 2.0;
    painter.drawEllipse(ellipse_central_x, ellipse_central_y,
                        ellipseWidth, ellipseHeight);
    painter.setPen(QPen(Qt::black));
    painter.drawLine(QPoint(0, 0), QPoint(0, -10));
    painter.restore();

    painter.drawEllipse(aPoint_, 10, 10);

}

int Human::generateHumanId() const
{
    std::default_random_engine engine(time(nullptr));    //设置了种子，每次种子都不一样
    std::uniform_int_distribution<> dis(0, 2147483647);    //设置了种子，每次种子都不一样
    return dis(engine);
}
