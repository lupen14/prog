#include "apple.h"
#include "roomBase.h"

#include "QDebug"

Apple::Apple(const QGraphicsScene *__scene) :
    QGraphicsItem(),
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

Mutagen Apple::getMutagen()
{
    return m_mutagen;
}

typeItem Apple::type() const
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
        if (listDirection.count() == 4)
            break;

        direction = static_cast<Movement::Direction>(rand() % Movement::ALL);

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

    if (!w)
        move(direction);
}

bool Apple::checkObstacles(const Movement::Direction &__direction)
{
    /// проверяем, есть ли по направлению куда хочет перемещаться яблоко стена или занята ли клетка каким-нибудь обьектом
    switch (__direction)
    {
        case Movement::DOWN:
        {
            if (this->y() + FIELD_SIZE > BORDER_MAX_Y || checkOutsiderItem(0, FIELD_SIZE))
                return true;

            break;
        }
        case Movement::UP:
        {
            if (this->y() - FIELD_SIZE < BORDER_MIN_Y || checkOutsiderItem(0, -FIELD_SIZE))
                return true;

            break;
        }
        case Movement::LEFT:
        {
            if (this->x() - FIELD_SIZE < BORDER_MIN_X || checkOutsiderItem(-FIELD_SIZE, 0))
                return true;

            break;
        }
        case Movement::RIGHT:
        {
            if (this->x() + FIELD_SIZE > BORDER_MAX_X || checkOutsiderItem(FIELD_SIZE, 0))
                return true;

            break;
        }
        case Movement::ALL:
            break;
    }

    return false;
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
        case Movement::ALL:
            break;
    }
}
