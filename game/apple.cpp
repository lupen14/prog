#include "apple.h"
#include "roomBase.h"

#include <QDebug>
#include <algorithm>    // std::shuffle
#include <vector>       // std::vector
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <vector>

Apple::Apple(const QGraphicsScene *__scene) :
    QGraphicsItem(),
    m_type(static_cast<itemType>(ItemType::APPLE)),
    m_size(-8, -8, 16, 16),
    m_appleSpeedMove(1000),
    m_pixmap(":apple/images/apple/apple.png"),
    m_move(false),
    m_mutagen(Mutagen::NONE)
{
    setRotation(Angle::ANGLE_0);

    //setPos(RoomBase::PLAYING_FIELD[rand()%FIELD_SIZE_X][rand()%FIELD_SIZE_Y]);

    positionDetermination(__scene);

    qDebug() << pos();
}

Apple::~Apple()
{
    emit signal_die(this);
}

void Apple::positionDetermination(const QGraphicsScene *__scene)
{
    QPointF applePos;
    do
    {
        applePos = RoomBase::PLAYING_FIELD[rand()%FIELD_SIZE_X][rand()%FIELD_SIZE_Y];

        QGraphicsItem *item = __scene->itemAt(applePos, QTransform());

        if (nullptr == item || item->zValue() == 0)
            break;

    } while (true);

    setPos(applePos);
}

void Apple::initTimer()
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &Apple::slot_appleTimer);
    m_timer->start(m_appleSpeedMove);
}

void Apple::dieTimer()
{
    m_timer->stop();
    disconnect(m_timer, &QTimer::timeout, this, &Apple::slot_appleTimer);
    delete m_timer;
    m_timer = nullptr;
}

QRectF Apple::boundingRect() const
{
    return m_size;
}

void Apple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(m_size, m_pixmap);

    Q_UNUSED(option); Q_UNUSED(widget);
}

void Apple::setMove(const bool &__move){
    m_move = __move;

    if (true == m_move)
        initTimer();
    else
        dieTimer();
}

bool Apple::getMove(){
    return m_move;
}

void Apple::setMutagen(const Mutagen &__mutagen)
{
    m_mutagen = __mutagen;

    switch (m_mutagen)
    {
        case Mutagen::ALL  :
        case Mutagen::NONE :
        {
            m_pixmap.load(":apple/images/apple/apple.png");
            break;
        }
        case Mutagen::SPEED :
        {
            m_pixmap.load(":apple/images/apple/apple_speed.png");
            break;
        }
    }
}

void Apple::setRandomMutagen()
{
    setMutagen(static_cast<Mutagen>(rand()%Mutagen::ALL));
}

itemType Apple::type() const
{
    return m_type;
}

void Apple::slot_appleTimer()
{
    Movement::Direction direction;

    direction = checkObstacles();

    if (direction != Movement::NONE)
        move(direction);
}

Movement::Direction Apple::checkObstacles()
{
    static std::vector<Movement::Direction> directions {Movement::DOWN, Movement::UP, Movement::LEFT, Movement::RIGHT};

    if (directions.size() == 0)
        return Movement::NONE;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);

    std::shuffle(directions.begin(), directions.end(), e);

    Movement::Direction direction(directions.back());

    /// ??????????????????, ???????? ???? ???? ?????????????????????? ???????? ?????????? ???????????????????????? ???????????? ?????????? ?????? ???????????? ???? ???????????? ??????????-???????????? ????????????????
    switch (direction)
    {
        case Movement::DOWN:
        {
            if (this->y() + FIELD_SIZE > BORDER_MAX_Y || checkOutsiderItem(0, FIELD_SIZE))
                return checkObstacles();

            break;
        }
        case Movement::UP:
        {
            if (this->y() - FIELD_SIZE < BORDER_MIN_Y || checkOutsiderItem(0, -FIELD_SIZE))
                return checkObstacles();

            break;
        }
        case Movement::LEFT:
        {
            if (this->x() - FIELD_SIZE < BORDER_MIN_X || checkOutsiderItem(-FIELD_SIZE, 0))
                return checkObstacles();

            break;
        }
        case Movement::RIGHT:
        {
            if (this->x() + FIELD_SIZE > BORDER_MAX_X || checkOutsiderItem(FIELD_SIZE, 0))
                return checkObstacles();

            break;
        }
        case Movement::NONE:
            break;
    }

    directions = {Movement::DOWN, Movement::UP, Movement::LEFT, Movement::RIGHT};

    return direction;
}

bool Apple::checkOutsiderItem(const int &__x = 0, const int &__y = 0)
{
    QGraphicsItem *item = scene()->itemAt(this->x() + __x, this->y() + __y, QTransform());

    if (nullptr == item)
        return false;

    if (item->zValue() == 0)
        return false;
    else
        return true;
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
        case Movement::NONE:
            break;
    }
}
