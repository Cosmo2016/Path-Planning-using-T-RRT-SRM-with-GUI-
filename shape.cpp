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
