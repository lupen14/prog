#include "snake.h"
#include "roomBase.h"

#include "QDebug"

using namespace Helper;

int Snake::count_eaten_apples = 0;

Snake::Snake(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    m_size(-8, -8, 16, 16)
{
    setRotation(Angle::ANGLE_0);
    this->setPos(RoomBase::PLAYING_FIELD[16][16]);
    //this->setPos(0,0);

    initTimer();
}

Snake::~Snake()
{
}

void Snake::initTimer()
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Snake::slot_snakeTimer);
    m_timer->start(SPEED_SNAKE);
}

void Snake::gameOver()
{
    emit signal_gameOver();
}

QRectF Snake::boundingRect() const
{
    return m_size;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(m_size, QPixmap(":snake/head.png"));

    Q_UNUSED(option); Q_UNUSED(widget);
}

void Snake::slot_snakeTimer()
{
    lastPos.clear();
    lastPos.append(QPointF(this->x(),this->y()));
    for (int i = 0; i < dots.count(); ++i) {
        lastPos.append(QPointF(dots.at(i)->x(), dots.at(i)->y()));
    }

    drivingDirections();

    move();

    checkWall();

    for (int i = 0; i < dots.count(); ++i) {
        dots.at(i)->setPos(lastPos.at(i));
    }

    collision();
}

void Snake::drivingDirections()
{
    if(GetAsyncKeyState(VK_LEFT)){
        if (directionHead != Movement::RIGHT)
        {
            this->setRotation(Angle::ANGLE_270);
            directionHead = Movement::LEFT;
        }
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        if (directionHead != Movement::LEFT)
        {
            this->setRotation(Angle::ANGLE_90);
            directionHead = Movement::RIGHT;
        }
    }
    if(GetAsyncKeyState(VK_UP)){
        if (directionHead != Movement::DOWN)
        {
            setRotation(Angle::ANGLE_0);
            directionHead = Movement::UP;
        }
    }
    if(GetAsyncKeyState(VK_DOWN)){
        if (directionHead != Movement::UP)
        {
            this->setRotation(Angle::ANGLE_180);
            directionHead = Movement::DOWN;
        }
    }
}

void Snake::move()
{
    this->setPos(mapToParent(0, -FIELD_SIZE));
}

void Snake::checkWall()
{
    if(this->x() - FIELD_HALF_SIZE < BORDER_MIN_X){
        gameOver();
        this->setX(BORDER_MIN_X + FIELD_HALF_SIZE);     // слева
    }
    if(this->x() + FIELD_HALF_SIZE > BORDER_MAX_X){
        gameOver();
        this->setX(BORDER_MAX_X - FIELD_HALF_SIZE);     // справа
    }
    if(this->y() - FIELD_HALF_SIZE < BORDER_MIN_Y){
        gameOver();
        this->setY(BORDER_MIN_Y + FIELD_HALF_SIZE);     // сверху
    }
    if(this->y() + FIELD_HALF_SIZE > BORDER_MAX_Y){
        gameOver();
        this->setY(BORDER_MAX_Y - FIELD_HALF_SIZE);     // снизу
    }
}

void Snake::collision()
{        
    QList<QGraphicsItem *> list = this->collidingItems();
    foreach(QGraphicsItem *item , list)
    {
        switch (item->type()) {
            case Apple::TYPE:
            {
                this->scene()->removeItem(item);
                delete item;

                count_eaten_apples++;

                addDot();

                break;
            }
            case Dot::TYPE:
            {
                /// удаляем тело до тех пор пока не удлим с тем с котом столкнулись
                while ( dots.lastIndexOf(item) > 0 )
                {
                    this->scene()->removeItem(dots.last());
                    delete dots.last();
                    dots.removeOne(dots.last());
                }
                break;
            }
        }
    }
}

void Snake::addDot()
{
    Dot *dot = new Dot(dots.isEmpty() ? this : dots.last());
    this->scene()->addItem(dot);
    dot->setPos(lastPos.last());
    dots.append(dot);
}
