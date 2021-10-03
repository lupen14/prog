#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "roomBase.h"

#include <QObject>

class LevelGenerator : public QObject
{
    Q_OBJECT

public:
    LevelGenerator(QGraphicsScene *__scene);
    ~LevelGenerator();

private:
    QGraphicsScene  *m_scene;
    RoomBase        *baseRoom;

    void startBaseLavel();
};

#endif // LEVELGENERATOR_H
