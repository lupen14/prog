#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

#include <windows.h>
#include "dot.h"
#include "apple.h"

class Snake : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Snake(QObject *parent = 0);
    ~Snake();

    static int count_eaten_apples;

signals:
    void signal_gameOver();

public slots:
    void slot_snakeTimer();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRect m_size;
    QList<QGraphicsItem *> dots;
    QList<QPointF> lastPos;
    char lastKey;

    // определяем направление движения головы
    void drivingDirections();

    // проверяем наличие стен
    void checkWall();

    // удлиняем тулвище
    void addDot();

    // движене змеи
    void move();

    // столкновение с другими обьектами
    void collision();

    // конец игры
    void gameOver();

    enum DIRECTION
    {
        UP      = 1,
        DOWN    = 2,
        RIGHT   = 3,
        LEFT    = 4
    };

    DIRECTION directionHead;
};

#endif // SNAKE_H
