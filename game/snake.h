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

using namespace Helper;

class Snake : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Snake(QObject *parent = 0);
    ~Snake();

    typeItem type() const;

    static int               count_eaten_apples;
    static const typeItem    TYPE = static_cast<typeItem>(ItemType::SNAKE);

signals:
    void signal_gameOver();

private slots:
    void slot_snakeTimer();
    void slot_setSnakeSpeed(snakeSpeed __speed);

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
    void addDot(const Mutagen &__mutagen);

    // движене змеи
    void move();

    // столкновение с другими обьектами
    void collision();

    // конец игры
    void gameOver();

    // записать скорость змейки
    void setSnakeSpeed(snakeSpeed __speed);


    Movement::Direction     directionHead;
    QRect                   m_size;
    QList<QGraphicsItem *>  dots;
    QList<QPointF>          lastPos;
    char                    lastKey;
    QTimer                  *m_timer;
    snakeSpeed              m_speed;
};

#endif // SNAKE_H
