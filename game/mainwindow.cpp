#include "mainwindow.h"
#include "ui_widget.h"

#include <QGraphicsPixmapItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(850,870);
    this->setFixedSize(850,870);

    configuringScene();

    levelGenerator = new RoomGenerator(scene);
}

void MainWindow::configuringScene()
{
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->graphicsView->scale(1.6,1.6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

