#include "roomBase.h"

#include "QDebug"
#include <QtAlgorithms>

QPointF RoomBase::PLAYING_FIELD[FIELD_SIZE_X][FIELD_SIZE_Y];

RoomBase::RoomBase(QGraphicsScene *__scene) :
m_scene(__scene)
{
    creatFieldMatrix();

    drawingSceneBoundaries();

    createSnake();

    initSnakeTimer();
}

RoomBase::~RoomBase()
{
}

void RoomBase::creatFieldMatrix()
{
    int field_x = 0;    
    for (int i = BORDER_MIN_X; i < BORDER_MAX_X; i+=FIELD_SIZE) {
        int field_y = 0;
        for (int j = BORDER_MIN_Y; j < BORDER_MAX_Y; j+=FIELD_SIZE) {
            PLAYING_FIELD[field_x][field_y] = QPointF(i + FIELD_HALF_SIZE, j + FIELD_HALF_SIZE);
            field_y++;
        }
        field_x++;
    }

    qDebug() << RoomBase::PLAYING_FIELD[16][16];
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

void RoomBase::initGameTimer()
{
    m_timerGame = new QTimer();
    connect(m_timerGame, &QTimer::timeout, this, &RoomBase::slot_gameTimer);
    m_timerGame->start(SPEED_GAME);
}

void RoomBase::slot_gameTimer()
{
    /*if (Snake::count_eaten_apples == 5)
    {
        m_timerSnake->stop();
        m_timerGame->stop();
        qDeleteAll(m_scene->items());
        m_snake = nullptr;
        emit signal_roomCompleted();
    }*/
}

void RoomBase::slot_appleDie(Apple *__apple)
{
    disconnect(__apple, &Apple::signal_die, this, &RoomBase::slot_appleDie);
    if (m_snake != nullptr)
        createApple();
}

void RoomBase::initSnakeTimer()
{
    m_timerSnake = new QTimer();
    connect(m_timerSnake, &QTimer::timeout, m_snake, &Snake::slot_snakeTimer);
    m_timerSnake->start(SPEED_SNAKE);
}

void RoomBase::slot_gameOver()
{
    exit(0);
}

