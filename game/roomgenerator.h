#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include "room_1_base.h"
#include "room_2_move_apple.h"

#include <QObject>

class RoomGenerator : public QObject
{
    Q_OBJECT

public:
    RoomGenerator(QGraphicsScene *__scene);
    ~RoomGenerator();

private:
    QGraphicsScene      *m_scene;
    Room_1_base         *room_1;
    Room_2_move_apple   *room_2;
    QList<RoomBase *>   rooms;

    // запуск первого уровня
    void startBaseLavel();

private slots:
    // успешное прохождение комнаты
    void slot_roomCompleted();

};

#endif // LEVELGENERATOR_H
