#include "room_2_move_apple.h"

Room_2_move_apple::Room_2_move_apple(QGraphicsScene *__scene) :
    RoomBase(__scene),
    m_scene(__scene)
{
    paintGrig();

    createSnake();

    createApple();

    initTimerRoom();
}

Room_2_move_apple::~Room_2_move_apple()
{
}

void Room_2_move_apple::createApple()
{
    Apple *apple = new Apple(m_scene);
    m_scene->addItem(apple);
    apple->setMove(true);
    apple->setRandomMutagen();
    connect(apple, &Apple::signal_die, this, &Room_2_move_apple::slot_appleDie);
}

void Room_2_move_apple::slot_appleDie(Apple *__apple)
{
    disconnect(__apple, &Apple::signal_die, this, &Room_2_move_apple::slot_appleDie);
    if (getSnake() != nullptr)
        createApple();
}
