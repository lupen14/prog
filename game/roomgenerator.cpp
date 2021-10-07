#include "roomgenerator.h"

RoomGenerator::RoomGenerator(QGraphicsScene *__scene):
    m_scene(__scene)
{
    startBaseLavel();
}

RoomGenerator::~RoomGenerator()
{
}

void RoomGenerator::startBaseLavel()
{
    room_2 = new Room_2_move_apple(m_scene);

    rooms.append(room_2);

    connect(rooms.last(), &RoomBase::signal_roomCompleted, this, &RoomGenerator::slot_roomCompleted);
}

void RoomGenerator::slot_roomCompleted()
{
    disconnect(rooms.last(), &RoomBase::signal_roomCompleted, this, &RoomGenerator::slot_roomCompleted);
    m_scene->clear();

    delete rooms.last();

    //startBaseLavel();
}
