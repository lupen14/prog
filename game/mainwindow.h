#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "levelgenerator.h"

#include <QMainWindow>
#include <QGraphicsScene>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsScene  *scene;
    LevelGenerator  *levelGenerator;

    // создаем сцену
    void configuringScene();

    Ui::MainWindow  *ui;
};

#endif // MAINWINDOW_H
