#include "levelgenerator.h"

LevelGenerator::LevelGenerator(QGraphicsScene *__scene):
    m_scene(__scene)
{
    startBaseLavel();
}

LevelGenerator::~LevelGenerator()
{
}

void LevelGenerator::startBaseLavel()
{
    baseRoom = new RoomBase(m_scene);
}
