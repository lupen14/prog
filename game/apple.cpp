#include "apple.h"
#include "roomBase.h"

#include "QDebug"

using namespace Helper;

Apple::Apple(const AppleFlags::Flags &__flag) :
    QGraphicsItem(),
    m_size(-8, -8, 16, 16),
    m_move(false),
    m_appleSpeed(1000)
{
    setRotation(Angle::ANGLE_0);

    srand(static_cast<unsigned int>(time(0)));
    setPos(RoomBase::PLAYING_FIELD[rand()%FIELD_SIZE_X][rand()%FIELD_SIZE_Y]);
    //setPos(RoomBase::PLAYING_FIELD[0][0]);

    parsingFlag(__flag);

    configuringApple();
}

Apple::~Apple()
{
    emit signal_die(this);
}

void Apple::parsingFlag(const AppleFlags::Flags &__flag)
{
    switch (__flag) {
        case AppleFlags::NORMAL:
        {
            break;
        }
        case AppleFlags::MOVE:
        {
            m_move = true;
            break;
        }
    }
}

void Apple::configuringApple()
{
    if (m_move == true)
    {
        initTimer();
    }
}

void Apple::initTimer()
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Apple::slot_appleTimer);
    m_timer->start(m_appleSpeed);
}

QRectF Apple::boundingRect() const
{
    return m_size;
}

void Apple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(m_size, QPixmap("apple.png"));

    Q_UNUSED(option); Q_UNUSED(widget);
}

int Apple::type() const
{
    return TYPE;
}

void Apple::slot_appleTimer()
{
    Movement::Direction direction;
    QList<Movement::Direction> listDirection;

    bool w = true;
    do
    {
        qDebug() << listDirection.count();
        if (listDirection.count() == 4)
            break;

        direction = static_cast<Movement::Direction>(rand() % Movement::ALL);

        qDebug() << direction;
        if (listDirection.contains(direction))
        {
            w = true;
        }
        else
        {
            listDirection.append(direction);

            w = checkObstacles(direction);
        }
    } while(w);

    move(direction);
}

bool Apple::checkObstacles(const Movement::Direction &__direction)
{
    /// проверяем, есть ли по направлению куда хочет перемещаться яблоко стена или занята ли клетка каким-нибудь обьектом
    switch (__direction)
    {
        case Movement::DOWN:
        {
            if (this->y() + FIELD_SIZE > BORDER_MAX_Y || nullptr != scene()->itemAt(this->x(), this->y() + FIELD_SIZE, QTransform()))
                return true;

            break;
        }
        case Movement::UP:
        {
            if (this->y() - FIELD_SIZE < BORDER_MIN_Y || nullptr != scene()->itemAt(this->x(), this->y() - FIELD_SIZE, QTransform()))
                return true;

            break;
        }
        case Movement::LEFT:
        {
            if (this->x() - FIELD_SIZE < BORDER_MIN_X || nullptr != scene()->itemAt(this->x() - FIELD_SIZE, this->y(), QTransform()))
                return true;

            break;
        }
        case Movement::RIGHT:
        {
            if (this->x() + FIELD_SIZE > BORDER_MAX_X || nullptr != scene()->itemAt(this->x() + FIELD_SIZE, this->y(), QTransform()))
                return true;

            break;
        }
        case Movement::ALL:
            break;
    }

    return false;
}

void Apple::move(const Movement::Direction &__direction)
{
    switch (__direction)
    {
        case Movement::DOWN:
        {
            this->setPos(mapToParent(0, FIELD_SIZE));
            break;
        }
        case Movement::UP:
        {
            this->setPos(mapToParent(0, -FIELD_SIZE));
            break;
        }
        case Movement::LEFT:
        {
            this->setPos(mapToParent(-FIELD_SIZE, 0));
            break;
        }
        case Movement::RIGHT:
        {
            this->setPos(mapToParent(FIELD_SIZE, 0));
            break;
        }
    }
}
