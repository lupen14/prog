#include "roomBase.h"


QPointF RoomBase::PLAYING_FIELD[FIELD_SIZE_X][FIELD_SIZE_Y];

RoomBase::RoomBase(QGraphicsScene *__scene) :
m_scene(__scene)
{
    creatFieldMatrix();

    drawingSceneBoundaries();

    paintGrig();

    createSnake();

    createApple();

    initGameTimer();
}

RoomBase::~RoomBase()
{
}

void RoomBase::creatFieldMatrix()
{
    int field_x = 0;
    for (int i = BORDER_MIN_X + FIELD_SIZE; i <= BORDER_MAX_X; i+=FIELD_SIZE) {
        int field_y = 0;
        for (int j = BORDER_MIN_Y + FIELD_SIZE; j <= BORDER_MAX_Y; j+=FIELD_SIZE) {
            PLAYING_FIELD[field_x][field_y] = QPointF(i,j);
            field_y++;
        }
        field_x++;
    }
}

void RoomBase::drawingSceneBoundaries()
{
    m_scene->setSceneRect(SCENE_X1, SCENE_Y1, SCENE_X2, SCENE_Y2);

    m_scene->addLine(BORDER_MIN_X, BORDER_MIN_Y, BORDER_MAX_X, BORDER_MIN_Y, QPen(Qt::black));
    m_scene->addLine(BORDER_MIN_X, BORDER_MAX_Y, BORDER_MAX_X, BORDER_MAX_Y, QPen(Qt::black));
    m_scene->addLine(BORDER_MIN_X, BORDER_MIN_Y, BORDER_MIN_X, BORDER_MAX_Y, QPen(Qt::black));
    m_scene->addLine(BORDER_MAX_X, BORDER_MIN_Y, BORDER_MAX_X, BORDER_MAX_Y, QPen(Qt::black));
}

void RoomBase::paintGrig()
{
    for (int i = BORDER_MIN_X; i <= BORDER_MAX_X; i+=FIELD_SIZE) {
        m_scene->addLine(i, BORDER_MAX_Y, i, BORDER_MIN_Y, QPen(Qt::lightGray));
        m_scene->addLine(BORDER_MAX_X, i, BORDER_MIN_X, i, QPen(Qt::lightGray));
    }
}

void RoomBase::createSnake()
{
    m_snake = new Snake();
    m_scene->addItem(m_snake);
    connect(m_snake, &Snake::signal_gameOver, this, &RoomBase::slot_gameOver);
}

void RoomBase::createApple()
{
    Apple *apple = new Apple();
    m_scene->addItem(apple);
    connect(apple, &Apple::signal_die, this, &RoomBase::slot_appleDie);
}

void RoomBase::slot_appleDie(Apple *__apple)
{
    disconnect(__apple, &Apple::signal_die, this, &RoomBase::slot_appleDie);
    createApple();
}


void RoomBase::initGameTimer()
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, m_snake, &Snake::slotGameTimer);
    m_timer->start(SPEED_GAME);
}

void RoomBase::slot_gameOver()
{
    exit(0);
}

