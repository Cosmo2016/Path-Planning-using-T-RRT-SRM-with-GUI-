#include "paintwidget.h"
#include <iostream>

#include "rect.h"
#include "utility.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), currShapeCode_(Shape::DepartPoint), shape_(NULL) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

PaintWidget::~PaintWidget()
{
    foreach (Shape *obstacle, this->obstacleList_) {
        delete obstacle;
    }
    delete this->starPoint_;
    delete this->goalPoint_;
}

QImage PaintWidget::getQImage()
{
    // cout << "QImage PaintWidget::getQImage()" << endl;
    QPixmap qPixmap = QWidget::grab();
    return qPixmap.toImage();
}

Human* PaintWidget::getHuman()
{
    return this->person_;
}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    // cout << "PaintWidget::paintEvent()" << endl;

    if (this->starPoint_) {
        this->starPoint_->paint(this);
    }
    if (this->goalPoint_) {
        this->goalPoint_->paint(this);
    }
    if (this->person_) {
        this->person_->paint(this);
    }

    // Draw human valid area
    foreach(MyPoint pointOfTest, this->validPointList4Test_) {
        // painter.drawPoint(pointOfPath);
        pointOfTest.paint(this);
    }

    // Draw path
    foreach(MyPoint pointOfPath, this->path_) {
        // painter.drawPoint(pointOfPath);
        pointOfPath.paint(this);
    }

    // Draw obstacles
    foreach(Shape *obstacle, this->obstacleList_) {
        obstacle->paint(this);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    // cout << "PaintWidget::mousePressEvent" << endl;

    switch (this->currShapeCode_) {
    case Shape::DepartPoint:
        if (this->starPoint_ == NULL)
        {
            this->starPoint_ = new Ellipse;
        }
        this->starPoint_->setQPenColor(Qt::red);
        this->starPoint_->setQBrushColor(Qt::red);
        this->starPoint_->setAPoint(event->pos());

        break;
    case Shape::DestPoint:
        if (this->goalPoint_ == NULL) {
            this->goalPoint_ = new Ellipse;
        }
        this->goalPoint_->setQPenColor(Qt::blue);
        this->goalPoint_->setQBrushColor(Qt::blue);
        this->goalPoint_->setAPoint(event->pos());
        break;
    case Shape::Rect: // Obstacle
        this->shape_ = new Rect;
        this->shape_->setQPenColor(Qt::black);
        this->shape_->setQBrushColor(Qt::black);
        this->shape_->setAPoint(event->pos());
        this->shape_->setBPoint(event->pos());
        // Add to list
        this->obstacleList_ << this->shape_;
        break;
    case Shape::Person:
        if (this->person_ == NULL) {
            this->person_ = new Human;
        }
        this->person_->setQPenColor(Qt::green);
        this->person_->setQBrushColor(Qt::green);
        this->person_->setAPoint(event->pos());
        break;
    }
    // this->repaint();
    this->update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    // cout << "PaintWidget::mouseMoveEvent" << endl;
    // ----------------------------------------------------------------------------------------------------------------------

    // for debug
    // if (this->person_) {
    if (false) {
        int tmp_x = event->pos().x();
        int tmp_y = event->pos().y();
        //cout << "(" << tmp_x << "," << tmp_y << ")";
        float searcherAngleWithXAxis = Utility::getIncludedAngle(
                    person_->getAPoint().x(),
                    person_->getAPoint().y(),
                    tmp_x, tmp_y);
        /*float distance = Utility::distanceBetween2Points(person_->getAPoint().x(),
                                                         person_->getAPoint().y(),
                                                         tmp_x, tmp_y);*/
        cout << " Angle With X-Axis = " << searcherAngleWithXAxis << endl;
        this->person_->setDirection(120);
        cout << "Human dir = " << this->person_->getDirection() << endl;
        // cout << " Two points distances = " << distance << endl;

        float includedAngle = searcherAngleWithXAxis - this->person_->getDirection();
        cout << "Included angle = " << includedAngle << endl;

        if (cos(includedAngle / 180 * M_PI) <= 0) {
            cout << "Back" <<  endl;
        } else {
            cout << "Front" <<  endl;
        }
    }

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
    // cout << "PaintWidget::mouseReleaseEvent" << endl;
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

void PaintWidget::add2PathList(QList<MyPoint> &point)
{

    this->path_.append(point);
    this->repaint(); // force to update UI
    // this->update();
}

void PaintWidget::clearPathList()
{
    this->path_.clear();
    this->validPointList4Test_.clear();
    this->repaint(); // force to update UI
    // this->update();
}

void PaintWidget::setCurrentShape(const Shape::Code currentShape)
{
    if (currentShape != this->currShapeCode_) {
        this->currShapeCode_ = currentShape;
    }
}

void PaintWidget::save2File()
{
    // cout << "PaintWidget::save2File()" << endl;
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
        cout << "Sava file success" << endl;
    } else {
        cout << "Sava file failed" << endl;
    }
}

void PaintWidget::addValidPointList4Test(QList<MyPoint> &testValidatedPoint)
{
    this->validPointList4Test_.append(testValidatedPoint);
}

void PaintWidget::clearValidPointList4Test()
{
    this->validPointList4Test_.clear();
    this->repaint(); // force to update UI
    // this->update();
}
