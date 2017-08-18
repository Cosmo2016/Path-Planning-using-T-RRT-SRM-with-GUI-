#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("OMPL"));

    QToolBar *bar = ui->mainToolBar;
    QActionGroup *group = new QActionGroup(bar);

    QAction *drawLineAction = new QAction("Line", bar);
    // drawLineAction->setIcon(QIcon(":/line.png"));
    drawLineAction->setToolTip(tr("Draw a line."));
    drawLineAction->setStatusTip(tr("Draw a line."));
    drawLineAction->setCheckable(true);
    drawLineAction->setChecked(true);
    group->addAction(drawLineAction);
    bar->addAction(drawLineAction);

    QAction *drawRectAction = new QAction("Rectangle", bar);
    // drawRectAction->setIcon(QIcon(":/rectangel.png"));
    drawRectAction->setToolTip(tr("Draw a rectangle."));
    drawRectAction->setStatusTip(tr("Draw a rectangle."));
    drawRectAction->setCheckable(true);
    group->addAction(drawRectAction);
    bar->addAction(drawRectAction);

    PaintWidget *paintWidget = new PaintWidget(this);
    setCentralWidget(paintWidget);

    connect(drawLineAction, SIGNAL(triggered()),
                    this, SLOT(drawLineActionTriggered()));
    connect(drawRectAction, SIGNAL(triggered()),
                    this, SLOT(drawRectActionTriggered()));
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
                    paintWidget, SLOT(setCurrentShape(Shape::Code)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLineActionTriggered()
{
    emit changeCurrentShape(Shape::Line);
}

void MainWindow::drawRectActionTriggered()
{
    emit changeCurrentShape(Shape::Rect);
}
