#ifndef ROOMBASE_H
#define ROOMBASE_H

#include "Helper.h"
#include "apple.h"
#include "snake.h"

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>

using namespace Base;

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
    void initTimerRoom();

    // сотворяем змейке
    void createSnake();

    // рисуем фон
    void drawBackgroung();

    // создаем портал
    void createPortal();

    Snake* getSnake() { return m_snake;};

signals:
    void signal_roomCompleted();

public slots:
    // слот таймера комнаты
    void slot_timerRoom();

    // слот конца игры
    void slot_gameOver();

    // слот когда яблоко сьедено
    virtual void slot_appleDie(Apple* __apple);

private:
    // определение матрицы полей
    void creatFieldMatrix();

    // отрисовка границ сцены
    void drawingSceneBoundaries();


    QGraphicsScene  *m_scene;
    Snake           *m_snake;
    QTimer          *m_timerRoom;
};

#endif // ROOMBASE_H
