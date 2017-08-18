#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QLabel>
#include <QToolBar>
#include <QStatusBar>


#include "shape.h"
#include "paintwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void changeCurrentShape(Shape::Code newShape);

private slots:
    void drawLineActionTriggered();
    void drawRectActionTriggered();
};

#endif // MAINWINDOW_H
