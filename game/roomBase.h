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

    // отрисовка сцены
    void paintGrig();

    // создание яблока
    virtual void createApple();

    // запуск игрового таймера
    void initGameTimer();

    Snake* getSnake() { return m_snake;};

signals:
    void signal_roomCompleted();

public slots:
    // слот игрового таймера
    void slot_gameTimer();

    // слот конца игры
    void slot_gameOver();

    // слот когда яблоко сьедено
    virtual void slot_appleDie(Apple* __apple);

private:
    QGraphicsScene  *m_scene;
    Snake           *m_snake;
    QTimer          *m_timerGame;

    // определение матрицы полей
    void creatFieldMatrix();

    // отрисовка границ сцены
    void drawingSceneBoundaries();

    // сотворяем змейке
    void createSnake();
};

#endif // ROOMBASE_H
