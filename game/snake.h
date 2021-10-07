#ifndef SNAKE_H
#define SNAKE_H

#include <windows.h>
#include "dot.h"
#include "apple.h"
#include "Helper.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class Snake : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Snake(QObject *parent = 0);
    ~Snake();

    static int count_eaten_apples;

signals:
    void signal_gameOver();

private slots:
    void slot_snakeTimer();

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    // оживляем змейку
    void initTimer();

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

    Movement::Direction     directionHead;
    QRect                   m_size;
    QList<QGraphicsItem *>  dots;
    QList<QPointF>          lastPos;
    char                    lastKey;
    QTimer                  *m_timer;
};

#endif // SNAKE_H
