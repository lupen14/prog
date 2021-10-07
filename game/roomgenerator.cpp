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
    room_1 = new Room_1_base(m_scene);

    rooms.append(room_1);

    connect(rooms.last(), &RoomBase::signal_roomCompleted, this, &RoomGenerator::slot_roomCompleted);
}

void RoomGenerator::slot_roomCompleted()
{
    disconnect(rooms.last(), &RoomBase::signal_roomCompleted, this, &RoomGenerator::slot_roomCompleted);
    m_scene->clear();

    delete rooms.last();

    //startBaseLavel();
}
