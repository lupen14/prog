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

signals:
    void signal_gameOver();

public slots:
    void slotGameTimer();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRect snakeSize;

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

    void gameOver();



    QList<QGraphicsItem *> dots;
    QList<QPointF> lastPos;
    char lastKey;


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
