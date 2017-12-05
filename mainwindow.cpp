#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plan2deviroment.h"
#include <thread>
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("Path planning using T-RRT SRM"));

    QToolBar *bar = ui->mainToolBar;
    QActionGroup *group = new QActionGroup(bar);

    QAction *drawDepartureAction = new QAction("Departure", bar);
    // drawLineAction->setIcon(QIcon(":/line.png"));
    drawDepartureAction->setToolTip(tr("Draw the departure point"));
    drawDepartureAction->setStatusTip(tr("Draw the departure point."));
    drawDepartureAction->setCheckable(true);
    drawDepartureAction->setChecked(true);
    group->addAction(drawDepartureAction);
    bar->addAction(drawDepartureAction);

    QAction *drawDesAction = new QAction("Destination", bar);
    // drawLineAction->setIcon(QIcon(":/line.png"));
    drawDesAction->setToolTip(tr("Draw the destination point"));
    // drawDesAction->setStatusTip(tr("Draw the destination point."));
    drawDesAction->setCheckable(true);
    // drawDesAction->setChecked(true);
    group->addAction(drawDesAction);
    bar->addAction(drawDesAction);

    QAction *drawRectAction = new QAction("Obstacle", bar);
    // drawRectAction->setIcon(QIcon(":/rectangel.png"));
    drawRectAction->setToolTip(tr("Draw obstacles"));
    // drawRectAction->setStatusTip(tr("Draw obstacles."));
    drawRectAction->setCheckable(true);
    group->addAction(drawRectAction);
    bar->addAction(drawRectAction);

    QAction *drawPersonAction = new QAction("Human", bar);
    // drawRectAction->setIcon(QIcon(":/rectangel.png"));
    drawPersonAction->setToolTip(tr("Draw a person"));
    // drawPersonAction->setStatusTip(tr("Draw a person"));
    drawPersonAction->setCheckable(true);
    group->addAction(drawPersonAction);
    bar->addAction(drawPersonAction);

    QAction *drawTestAction = new QAction("Test Human", bar);
    // drawRectAction->setIcon(QIcon(":/rectangel.png"));
    drawTestAction->setToolTip(tr("Test valid area "));
    // drawPersonAction->setStatusTip(tr("Draw a person"));
    drawTestAction->setCheckable(true);
    group->addAction(drawTestAction);
    bar->addAction(drawTestAction);

    QAction *pathPlanAction = new QAction("Plan start", bar);
    pathPlanAction->setToolTip(tr("Plan start"));
    // pathPlanAction->setStatusTip(tr("Plan start"));
    pathPlanAction->setCheckable(true);
    group->addAction(pathPlanAction);
    bar->addAction(pathPlanAction);

    QAction *saveFileAction = new QAction("Save file", bar);
    saveFileAction->setToolTip(tr("Save file"));
    // saveFileAction->setStatusTip(tr("Save file to disk."));
    saveFileAction->setCheckable(true);
    group->addAction(saveFileAction);
    bar->addAction(saveFileAction);

    paintWidget = new PaintWidget(this);
    setCentralWidget(paintWidget);
    QPalette pal(paintWidget->palette());
    pal.setColor(QPalette::Background, Qt::white);
    paintWidget->setAutoFillBackground(true);
    paintWidget->setPalette(pal);
    // paintWidget->show();

    connect(drawDepartureAction, SIGNAL(triggered()),
                    this, SLOT(drawDepartureActionTriggered()));
    connect(drawDesAction, SIGNAL(triggered()),
                    this, SLOT(drawDestinationActionTriggered()));
    connect(drawRectAction, SIGNAL(triggered()),
                    this, SLOT(drawRectActionTriggered()));
    connect(pathPlanAction, SIGNAL(triggered()),
                    this, SLOT(pathPlanActionTriggered()));
    connect(saveFileAction, SIGNAL(triggered()),
                    this, SLOT(saveFileActionTriggered()));
    connect(drawTestAction, SIGNAL(triggered()),
                    this, SLOT(drawTestActionTriggered()));
    // Draw a person
    connect(drawPersonAction, SIGNAL(triggered()),
                    this, SLOT(drawPersonActionTriggered()));

    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
                    paintWidget, SLOT(setCurrentShape(Shape::Code)));
    connect(this, SIGNAL(saveFileToDisk()),
                    paintWidget, SLOT(save2File()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawDepartureActionTriggered()
{
    emit changeCurrentShape(Shape::DepartPoint);
}

void MainWindow::drawDestinationActionTriggered()
{
    emit changeCurrentShape(Shape::DestPoint);
}

void MainWindow::drawRectActionTriggered()
{
    emit changeCurrentShape(Shape::Rect);
}

void MainWindow::drawPersonActionTriggered()
{
    emit changeCurrentShape(Shape::Person);
}


/**
 * Multi-thread
 *
 * @brief call_thread_path_planner
 * @param paintWidget
 */
void call_thread_path_planner(PaintWidget *paintWidget)
{
    Plan2DEviroment plan2DEviroment(paintWidget);
    QPoint startPoint = paintWidget->getStartPoint();
    QPoint goalPoint = paintWidget->getGoalPoint();

    if (plan2DEviroment.plan(startPoint.y(), startPoint.x(),
                             goalPoint.y(), goalPoint.x())) {
        QList<MyPoint> pathPointList = plan2DEviroment.recordSolution();
        paintWidget->add2PathList(pathPointList);
    } /*else {
        // Should show failed message to UI
    }*/

}

void MainWindow::pathPlanActionTriggered()
{
    this->statusBar()->showMessage("Path searching starting....", 3000);
    paintWidget->clearPathList();
    std::thread pathPlannerThread(call_thread_path_planner,
                                  this->paintWidget);
    pathPlannerThread.detach();
}

void MainWindow::saveFileActionTriggered()
{
    emit saveFileToDisk();
}

void MainWindow::drawTestActionTriggered()
{
    Plan2DEviroment plan2DEviroment(paintWidget);

    QList<QPointF*> tmpValidateList;

    for (int i = 0; i < 400000; ++i) {
        QPointF *tmpTestOkPoint = plan2DEviroment.testHumanValidArea();
        if(tmpTestOkPoint) {
            tmpValidateList << tmpTestOkPoint;
        }
    }

    // paintWidget->addValidPointList4Test(tmpValidateList);

    size_t matrix[paintWidget->width()][paintWidget->height()];

    for (int i = 0; i < paintWidget->width(); ++i) {
        for (int j = 0; j < paintWidget->height(); ++j) {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < tmpValidateList.size(); ++i) {
        QPointF* tmp = tmpValidateList.at(i);
        size_t tmp_x = tmp->x();
        size_t tmp_y = tmp->y();
        if (matrix[tmp_x][tmp_y] <= 255) {
            matrix[tmp_x][tmp_y] += 10;
        }
    }

    for (int i = 0; i < tmpValidateList.size(); ++i) {
        delete tmpValidateList[i];
    }

    QList<MyPoint> lastConveretedValidatedPoint;

    for (int i = 0; i < paintWidget->width(); ++i) {
        for (int j = 0; j < paintWidget->height(); ++j) {
            if(matrix[i][j] != 0) {
                MyPoint tmpValidatedPoint;
                tmpValidatedPoint.setAPoint(QPoint(i, j));
                tmpValidatedPoint.setQPenColor(QColor(255, 0, 0, matrix[i][j]));
                lastConveretedValidatedPoint << tmpValidatedPoint;
            }
        }
    }

    paintWidget->clearValidPointList4Test();
    paintWidget->addValidPointList4Test(lastConveretedValidatedPoint);
}
