#ifndef ROOM_1_BASE_H
#define ROOM_1_BASE_H

/* #########################
 * #
 * #     Комната # 1
 * # В данной комнате нужно собрать 5 яблок для прохождения этой комнаты
 * #
 * ########################
*/

#include "roomBase.h"

#include <QObject>

class Room_1_base : public RoomBase
{
    Q_OBJECT
public:
    Room_1_base(QGraphicsScene *__scene);
    ~Room_1_base();

private:
    QGraphicsScene *m_scene;

signals:

};

#endif // ROOM_1_BASE_H
