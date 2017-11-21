#include "shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

void Shape::setAPoint(const QPoint aPoint)
{
    this->aPoint_ = aPoint;
}

QPoint Shape::getAPoint() const
{
    return this->aPoint_;
}

void Shape::setBPoint(const QPoint bPoint)
{
    this->bPoint_ = bPoint;
}

QPoint Shape::getBPoint() const
{
    return this->bPoint_;
}

void Shape::setQBrush(const QBrush qBrush)
{
    this->qBrush_ = qBrush;
}

QBrush Shape::getQBursh() const
{
    return this->qBrush_;
}

void Shape::setQPen(const QPen &qPen)
{
    this->qPen_ = qPen;
}

QPen Shape::getQPen() const
{
    return this->qPen_;
}
