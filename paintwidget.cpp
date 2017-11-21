#include "paintwidget.h"
#include <iostream>

#include "line.h"
#include "rect.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), currShapeCode_(Shape::DepartPoint), shape_(NULL) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

PaintWidget::~PaintWidget()
{
    foreach (Shape *shape, this->obstacleList_) {
        delete shape;
    }
    delete this->starPoint_;
    delete this->goalPoint_;
}

QImage PaintWidget::getQImage()
{
    cout << "getQImage" << endl;
    QPixmap qPixmap = QWidget::grab();
    return qPixmap.toImage();
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    cout << "PaintWidget::paintEvent" << endl;

    foreach(Shape *obstacle, this->obstacleList_) {
        obstacle->paint(this);
    }

    if (this->starPoint_) {
        this->starPoint_->paint(this);
    }
    if (this->goalPoint_) {
        this->goalPoint_->paint(this);
    }
    if (this->person_) {
        this->person_->paint(this);
    }

    // Draw path
    foreach(Point pointOfPath, this->path_) {
        // painter.drawPoint(pointOfPath);
        pointOfPath.paint(this);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    cout << "PaintWidget::mousePressEvent" << endl;
    QPainter painter(this);

    switch (this->currShapeCode_) {
    case Shape::DepartPoint:
        if (this->starPoint_ == NULL)
        {
            this->starPoint_ = new Ellipse;
        }
        this->starPoint_->setQPen(QPen(Qt::red));
        this->starPoint_->setQBrush(QBrush(Qt::red));
        this->starPoint_->setAPoint(event->pos());
        break;
    case Shape::DestPoint:
        if (this->goalPoint_ == NULL) {
            this->goalPoint_ = new Ellipse;
        }
        this->goalPoint_->setQPen(QPen(Qt::blue));
        this->goalPoint_->setQBrush(QBrush(Qt::blue));
        this->goalPoint_->setAPoint(event->pos());
        break;
    case Shape::Rect: // Obstacle
        this->shape_ = new Rect;
        this->shape_->setQPen(QPen(Qt::black));
        this->shape_->setQBrush(QBrush(Qt::black));
        this->shape_->setAPoint(event->pos());
        this->shape_->setBPoint(event->pos());
        // Add to list
        this->obstacleList_ << this->shape_;
        break;
    case Shape::Person:
        if (this->person_ == NULL) {
            this->person_ = new Ellipse;
        }
        this->person_->setQPen(QPen(Qt::green));
        this->person_->setQBrush(QBrush(Qt::green));
        this->person_->setAPoint(event->pos());
        break;
    }
    // this->repaint();
    this->update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    cout<<"PaintWidget::mouseMoveEvent"<<endl;

    switch (this->currShapeCode_) {
    case Shape::DepartPoint:
        this->starPoint_->setAPoint(event->pos());
        break;
    case Shape::DestPoint:
        this->goalPoint_->setAPoint(event->pos());
        break;
    case Shape::Person:
        this->person_->setAPoint(event->pos());
        break;
    default:
        if (this->shape_) {
            this->shape_->setBPoint(event->pos());
        }
    }

    //this->repaint();
    this->update();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    cout << "PaintWidget::mouseReleaseEvent" << endl;
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

void PaintWidget::addPathPoint(QList<Point> &point)
{
    this->path_.clear();
    this->path_.append(point);
    this->repaint(); // force to update UI
}

void PaintWidget::setCurrentShape(const Shape::Code currentShape)
{
    if (currentShape != this->currShapeCode_) {
        this->currShapeCode_ = currentShape;
    }
}

void PaintWidget::save2File()
{
    cout << "Save file" << endl;
    QPixmap qPixmap;
    qPixmap = QWidget::grab();
    QImage qImage = qPixmap.toImage();

    // for test / sample
    /* QPoint qPoint(0, 50);
    QColor qColor(0, 0, 0);
    for (int i = 0; i < 100; ++i) {
        qImage.setPixelColor(qPoint, qColor);
        qPoint.setX(i);
    } */

    if (qImage.save("/Volumes/Cosmo/aaa.ppm", "PPM")) {
        // this->qPixmap(this->size());
        // this->render(&this->qPixmap);
        this->render(&qImage);
        cout << "sava file success" << endl;
    } else {
        cout << "sava file fail" << endl;
    }
}
