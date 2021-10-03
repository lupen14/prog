#ifndef ROOMBASE_H
#define ROOMBASE_H

#include "Helper.h"
#include "apple.h"
#include "snake.h"

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>

using namespace Helper;

class RoomBase : public QObject
{
    Q_OBJECT

public:
    RoomBase(QGraphicsScene *__scene);
    ~RoomBase();

    static QPointF PLAYING_FIELD[FIELD_SIZE_X][FIELD_SIZE_Y];

private slots:
    void slot_gameOver();
    void slot_appleDie(Apple* __apple);

private:
    QGraphicsScene  *m_scene;
    Snake           *m_snake;
    QTimer          *m_timer;

    // определение матрицы полей
    void creatFieldMatrix();

    // отрисовка границ сцены
    void drawingSceneBoundaries();

    // отрисовка сцены
    void paintGrig();

    // создание яблока
    void createApple();

    // сотворяем змейке
    void createSnake();

    // запуск игрового таймера
    void initGameTimer();
};

#endif // ROOMBASE_H
