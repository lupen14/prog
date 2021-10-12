#include "roomBase.h"

#include "portal.h"

#include "QDebug"
#include <QtAlgorithms>

QPointF RoomBase::PLAYING_FIELD[FIELD_SIZE_X][FIELD_SIZE_Y];

RoomBase::RoomBase(QGraphicsScene *__scene) :
m_scene(__scene)
{
    drawBackgroung();

    creatFieldMatrix();

    drawingSceneBoundaries();
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
        m_scene->addLine(i, BORDER_MAX_Y, i, BORDER_MIN_Y, QPen(QColor("#183b14")));
        m_scene->addLine(BORDER_MAX_X, i, BORDER_MIN_X, i, QPen(QColor("#183b14")));
    }
}

void RoomBase::createSnake()
{
    m_snake = new Snake();
    m_scene->addItem(m_snake);
    connect(m_snake, &Snake::signal_gameOver, this, &RoomBase::slot_gameOver);
}

void RoomBase::drawBackgroung()
{
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(":background/images/background/grass.png"));
    m_scene->addItem(item);
    item->setPos(SCENE_X1, SCENE_Y1);
    item->setZValue(ItemZValue::Z_BACKGROUND);
}

void RoomBase::createApple()
{
    Apple *apple = new Apple(m_scene);
    m_scene->addItem(apple);
    connect(apple, &Apple::signal_die, this, &RoomBase::slot_appleDie);
}

void RoomBase::initTimerRoom()
{
    m_timerRoom = new QTimer();
    connect(m_timerRoom, &QTimer::timeout, this, &RoomBase::slot_timerRoom);
    m_timerRoom->start(Helper::SPEED_GAME);
}

void RoomBase::slot_timerRoom()
{
    if (Snake::count_eaten_apples == 1)
    {
        m_timerRoom->stop();
        createPortal();
    }
}

void RoomBase::createPortal()
{
    Portal *portal = new Portal();
    m_scene->addItem(portal);
    portal->setPos(PLAYING_FIELD[15][2]);
    connect(portal, &Portal::s_coincidence, this, &RoomBase::slot_gameOver);
}

void RoomBase::slot_appleDie(Apple *__apple)
{
    disconnect(__apple, &Apple::signal_die, this, &RoomBase::slot_appleDie);
    if (m_snake != nullptr)
        createApple();
}

void RoomBase::slot_gameOver()
{
    qDeleteAll(m_scene->items());
    m_snake = nullptr;
    emit signal_roomCompleted();

    exit(0);
}

