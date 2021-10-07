#include "room_1_base.h"

Room_1_base::Room_1_base(QGraphicsScene *__scene) :
    RoomBase(__scene),
    m_scene(__scene)
{
    paintGrig();

    createApple();

    initGameTimer();
}

Room_1_base::~Room_1_base()
{
}
