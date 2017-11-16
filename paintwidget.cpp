#include "paintwidget.h"
#include <iostream>

#include "line.h"
#include "rect.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), currShapeCode_(Shape::DepartPoint), shape_(NULL) /*,perm(false)*/
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

PaintWidget::~PaintWidget()
{
    foreach(Shape *shape, this->shapeList_)
    {
        delete shape;
    }
    delete this->starPoint_;
    delete this->goalPoint_;
}

QImage PaintWidget::getQImage()
{
    cout<<"getQImage"<<endl;
    QPixmap qPixmap = QWidget::grab();
    return qPixmap.toImage();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
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

    // draw path
    foreach(QPoint path, this->path_)
    {
        painter.drawPoint(path);
    }
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
            this->starPoint_->setQPen(QPen(Qt::red));
            this->starPoint_->setQBrush(QBrush(Qt::red));
            this->starPoint_->setAPoint(event->pos());
            break;
        }
        case Shape::DestPoint:
        {
            if (this->goalPoint_ == NULL)
            {
                this->goalPoint_ = new Ellipse;
            }
            this->goalPoint_->setQPen(QPen(Qt::blue));
            this->goalPoint_->setQBrush(QBrush(Qt::blue));
            this->goalPoint_->setAPoint(event->pos());
            break;
        }
        case Shape::Rect:
        {
            this->shape_ = new Rect;
            this->shape_->setQPen(QPen(Qt::black));
            this->shape_->setQBrush(QBrush(Qt::black));
            this->shapeList_<<this->shape_;
            this->shape_->setAPoint(event->pos());
            this->shape_->setBPoint(event->pos());
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
        this->starPoint_->setAPoint(event->pos());
    }
    if (this->currShapeCode_ == Shape::DestPoint)
    {
        this->goalPoint_->setAPoint(event->pos());
    }
    if(this->shape_)
    {
        this->shape_->setBPoint(event->pos());
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

QPoint PaintWidget::getStartPoint()
{
    return QPoint(this->starPoint_->getAPoint().x(),
                  this->starPoint_->getAPoint().y());
}
QPoint PaintWidget::getGoalPoint()
{
    return QPoint(this->goalPoint_->getAPoint().x(),
                  this->goalPoint_->getAPoint().y());
}

void PaintWidget::addPathPoint(QList<QPoint> pPoint)
{
    this->path_.append(pPoint);
    this->repaint();
}

void PaintWidget::setCurrentShape(const Shape::Code currentShape)
{
    if(currentShape != this->currShapeCode_)
    {
        this->currShapeCode_ = currentShape;
    }
    /*if(pen != this->currPen_)
    {
        this->currPen_ = pen;
    }
    if(brush != this->currBrush_)
    {
        this->currBrush_ = brush;
    }*/
}

void PaintWidget::saveFile()
{
    cout<<"Save file"<<endl;
    QPixmap qPixmap;
    qPixmap = QWidget::grab();
    QImage qImage = qPixmap.toImage();

    // for test / sample
    /* QPoint qPoint(0, 50);
    QColor qColor(0, 0, 0);
    for (int i = 0; i < 100; ++i)
    {
        qImage.setPixelColor(qPoint, qColor);
        qPoint.setX(i);
    } */


    if (qImage.save("/Volumes/Cosmo/aaa.ppm", "PPM"))
    {
        // this->qPixmap(this->size());
        // this->render(&this->qPixmap);
        this->render(&qImage);
        cout<<"sava file success"<<endl;
    }
    else
    {
        cout<<"sava file fail"<<endl;
    }
}
