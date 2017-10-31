#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>

class Shape
{
public:
    enum Code {
        DepartPoint,
        DestPoint,
        // Line,
        Rect
    };

    Shape();
    virtual ~Shape();

    void setAPoint(QPoint s) {
        this->aPoint_ = s;
    }

    void setBPoint(QPoint e) {
        this->bPoint_ = e;
    }

    QPoint getAPoint() {
        return this->aPoint_;
    }

    QPoint getBPoint() {
        return this->bPoint_;
    }

    void setQBrush(const QBrush &qBrush)
    {
        this->qBrush_ = qBrush;
    }

    QBrush getQBursh() const
    {
        return this->qBrush_;
    }

    void setQPen(const QPen &qPen)
    {
        this->qPen_ = qPen;
    }

    QPen getQPen() const
    {
        return this->qPen_;
    }

    void virtual paint(QPainter & painter) = 0;

protected:
    QPoint aPoint_;
    QPoint bPoint_;

    QBrush qBrush_;
    QPen qPen_;
};

#endif // SHAPE_H
