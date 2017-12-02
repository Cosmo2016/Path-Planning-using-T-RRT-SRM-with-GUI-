#include "shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
}

void Shape::setAPoint(const QPointF aPoint)
{
    this->aPoint_ = aPoint;
}

QPointF Shape::getAPoint() const
{
    return this->aPoint_;
}

void Shape::setBPoint(const QPointF bPoint)
{
    this->bPoint_ = bPoint;
}

QPointF Shape::getBPoint() const
{
    return this->bPoint_;
}

void Shape::setQBrushColor(const QColor brushColor)
{
    this->brushColor_ = brushColor;
}

QBrush Shape::getQBurshColor() const
{
    return this->brushColor_;
}

void Shape::setQPenColor(const QColor penColor)
{
    this->penColor_ = penColor;
}

QPen Shape::getQPenColor() const
{
    return this->penColor_;
}
