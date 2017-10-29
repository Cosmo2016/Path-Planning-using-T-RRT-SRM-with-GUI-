#include "paintwidget.h"
#include <iostream>

#include "line.h"
#include "rect.h"
#include "ellipse.h"

using namespace std;

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), currShapeCode_(Shape::DepartPoint), shape_(NULL), perm(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // QPaintEvent::registerEventType(8699);

}

PaintWidget::~PaintWidget()
{

}

QImage PaintWidget::getQImage()
{
    cout<<"getQImage"<<endl;
    QPixmap qPixmap = QWidget::grab();
    return qPixmap.toImage();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    /*if (event->type() == 8699)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, this->size().height(), this->size().width(), qPixmap);
    }*/
    cout<<"PaintWidget::paintEvent"<<endl;
    QPainter painter(this);
    /*painter.setPen(Qt::red);
    painter.setBrush(Qt::black);*/
    // painter.drawRect(0, 0, size().width(), size().height());

    foreach(Shape *shape, this->shapeList_)
    {
        shape->paint(painter);
    }
    if (this->starPoint_)
    {
        this->starPoint_->paint(painter);
    }
    if (this->goalPoint_)
    {
        this->goalPoint_->paint(painter);
    }
    /*if(shape)
    {
        shape->paint(painter);
    }*/
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    cout<<"PaintWidget::mousePressEvent"<<endl;
    QPainter painter(this);

    switch(this->currShapeCode_)
    {
        // perm = false;
        case Shape::DepartPoint:
        {
            if (this->starPoint_ == NULL)
            {
                this->starPoint_ = new Ellipse;
            }
            this->starPoint_->setQPen(QPen(Qt::black));
            this->starPoint_->setQBrush(QBrush(Qt::red));
            this->starPoint_->setStart(event->pos());
            break;
        }
        case Shape::DestPoint:
        {
            if (this->goalPoint_ == NULL)
            {
                this->goalPoint_ = new Ellipse;
            }
            this->goalPoint_->setQPen(QPen(Qt::black));
            this->goalPoint_->setQBrush(QBrush(Qt::blue));
            this->goalPoint_->setStart(event->pos());
            break;
        }
        case Shape::Rect:
        {
            this->shape_ = new Rect;
            this->shape_->setQPen(QPen(Qt::black));
            this->shape_->setQBrush(QBrush(Qt::black));
            this->shapeList_<<this->shape_;
            this->shape_->setStart(event->pos());
            this->shape_->setEnd(event->pos());
            break;
        }
    }
    /*if(shape != NULL)
    {
        perm = false;
        this->shapeList_<<shape;
        shape->setStart(event->pos());
        shape->setEnd(event->pos());
    }*/
    this->repaint();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    cout<<"PaintWidget::mouseMoveEvent"<<endl;
    // if(this->shape_ && !perm)
    if(this->currShapeCode_ == Shape::DepartPoint)
    {
        this->starPoint_->setStart(event->pos());
    }
    if (this->currShapeCode_ == Shape::DestPoint)
    {
        this->goalPoint_->setStart(event->pos());
    }
    if(this->shape_)
    {
        this->shape_->setEnd(event->pos());
    }

    // this->update();
    this->repaint();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    cout<<"PaintWidget::mouseReleaseEvent"<<endl;
    //  = true;
    this->shape_ = NULL;
}
