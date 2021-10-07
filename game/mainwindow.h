#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "roomgenerator.h"

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
    RoomGenerator   *levelGenerator;

    // создаем сцену
    void configuringScene();

    Ui::MainWindow  *ui;
};

#endif // MAINWINDOW_H
