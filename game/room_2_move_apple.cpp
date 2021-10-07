#include "room_2_move_apple.h"

Room_2_move_apple::Room_2_move_apple(QGraphicsScene *__scene) :
    RoomBase(__scene),
    m_scene(__scene)
{
    paintGrig();

    createApple();

    initGameTimer();
}

Room_2_move_apple::~Room_2_move_apple()
{
}

void Room_2_move_apple::createApple()
{
    Apple *apple = new Apple(AppleFlags::MOVE);
    m_scene->addItem(apple);
    connect(apple, &Apple::signal_die, this, &Room_2_move_apple::slot_appleDie);
}

void Room_2_move_apple::slot_appleDie(Apple *__apple)
{
    disconnect(__apple, &Apple::signal_die, this, &Room_2_move_apple::slot_appleDie);
    if (getSnake() != nullptr)
        createApple();
}
