#ifndef ROOM_2_MOVE_APPLE_H
#define ROOM_2_MOVE_APPLE_H

/* #########################
 * #
 * #     Комната # 2
 * # В данной комнате нужно собрать 5  убегающих яблок для прохождения этой комнаты
 * # Особености карты: яблоки умеют бегать!
 * #
 * ########################
*/

#include "roomBase.h"

#include <QObject>

class Room_2_move_apple : public RoomBase
{
    Q_OBJECT
public:
    Room_2_move_apple(QGraphicsScene *__scene);
    ~Room_2_move_apple();

private:
    virtual void createApple();

    QGraphicsScene *m_scene;

public slots:
    virtual void slot_appleDie(Apple* __apple);

};

#endif // ROOM_2_MOVE_APPLE_H
