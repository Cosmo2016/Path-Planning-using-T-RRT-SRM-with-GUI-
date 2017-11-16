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
    drawDesAction->setStatusTip(tr("Draw the destination point."));
    drawDesAction->setCheckable(true);
    // drawDesAction->setChecked(true);
    group->addAction(drawDesAction);
    bar->addAction(drawDesAction);

    QAction *drawRectAction = new QAction("Obstacle", bar);
    // drawRectAction->setIcon(QIcon(":/rectangel.png"));
    drawRectAction->setToolTip(tr("Draw obstacles"));
    drawRectAction->setStatusTip(tr("Draw obstacles."));
    drawRectAction->setCheckable(true);
    group->addAction(drawRectAction);
    bar->addAction(drawRectAction);

    QAction *pathPlanAction = new QAction("Plan start", bar);
    pathPlanAction->setToolTip(tr("Plan start"));
    pathPlanAction->setStatusTip(tr("Plan start"));
    pathPlanAction->setCheckable(true);
    group->addAction(pathPlanAction);
    bar->addAction(pathPlanAction);

    QAction *saveFileAction = new QAction("Save file", bar);
    saveFileAction->setToolTip(tr("Save file"));
    saveFileAction->setStatusTip(tr("Save file to disk."));
    saveFileAction->setCheckable(true);
    group->addAction(saveFileAction);
    bar->addAction(saveFileAction);

    // PaintWidget *paintWidget = new PaintWidget(this);
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

    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
                    paintWidget, SLOT(setCurrentShape(Shape::Code)));
    connect(this, SIGNAL(saveFileToDisk()),
                    paintWidget, SLOT(saveFile()));
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
                             goalPoint.y(), goalPoint.x()))
    {
        QList<QPoint> pathPoint = plan2DEviroment.recordSolution();
        // this->paintWidget->addPathPoint(pathPoint);
        paintWidget->addPathPoint(pathPoint);
    }
}

void MainWindow::pathPlanActionTriggered()
{
    std::thread pathPlannerThread(call_thread_path_planner,
                                  std::ref(this->paintWidget));
    pathPlannerThread.join();
}

void MainWindow::saveFileActionTriggered()
{
    emit saveFileToDisk();
}
