#include "snake.h"
#include "roomBase.h"

#include "QDebug"

using namespace Base;

int Snake::count_eaten_apples = 0;

Snake::Snake(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    m_size(-8, -8, 16, 16),
    m_speed(5)
{
    setRotation(Angle::ANGLE_0);
    this->setPos(RoomBase::PLAYING_FIELD[16][16]);
    //this->setPos(0,0);

    this->setZValue(ItemZValue::Z_SNAKE);

    initTimer();
}

Snake::~Snake()
{
}

QRectF Snake::boundingRect() const
{
    return m_size;
}

int Snake::type() const
{
    return TYPE;
}

void Snake::initTimer()
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Snake::slot_snakeTimer);
    m_timer->start((int)(1000 / m_speed));
}

void Snake::gameOver()
{
    emit signal_gameOver();
}

void Snake::setSnakeSpeed(snakeSpeed __speed)
{

    m_speed += __speed;
    m_timer->start((int)(1000 / m_speed));
    qDebug() << m_speed;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(m_size, QPixmap(":snake/images/snake/head.png"));

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
    for(QGraphicsItem *item : list)
    {
        switch (item->type()) {
            case static_cast<typeItem>(ItemType::APPLE):
            {
                Apple *apple = static_cast<Apple*>(item);
                addDot(apple->getMutagen());
                this->scene()->removeItem(item);
                delete item;
                item = nullptr;

                count_eaten_apples++;

                break;
            }
            case static_cast<typeItem>(ItemType::DOT):
            {
                /// удаляем тело до тех пор пока не удлим с тем с котом столкнулись
                while ( dots.lastIndexOf(item) > 0 )
                {
                    Dot *lastDot(static_cast<Dot*>(dots.last()));
                    lastDot->printBload();

                    if (lastDot->getMutagen() == Mutagen::SPEED)
                    {
                        disconnect(lastDot, &Dot::signal_setSnakeSpeed, this, &Snake::slot_setSnakeSpeed);
                    }

                    dots.removeOne(lastDot);

                    this->scene()->removeItem(lastDot);
                    delete lastDot;
                    lastDot = nullptr;
                }
                break;
            }
        }
    }
}

void Snake::addDot(const Mutagen &__mutagen)
{
    Dot *dot = new Dot(dots.isEmpty() ? this : dots.last());

    switch (__mutagen)
    {
        case Mutagen::NONE :
        {
            dot->setMutagenNone();
            break;
        }
        case Mutagen::SPEED :
        {
            connect(dot, &Dot::signal_setSnakeSpeed, this, &Snake::slot_setSnakeSpeed);
            dot->setMutagenSpeed();
            break;
        }
        case Mutagen::ALL :
        {
            break;
        }
    }

    this->scene()->addItem(dot);
    dot->setPos(lastPos.last());
    dots.append(dot);
}

void Snake::slot_setSnakeSpeed(snakeSpeed __speed)
{
    setSnakeSpeed(__speed);
}











