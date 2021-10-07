#include "apple.h"
#include "roomBase.h"

#include "QDebug"

using namespace Helper;

Apple::Apple(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    m_size(-8, -8, 16, 16)
{
    setRotation(0);
    srand(static_cast<unsigned int>(time(0)));
    setPos(RoomBase::PLAYING_FIELD[rand()%FIELD_SIZE_X][rand()%FIELD_SIZE_Y]);
    //setPos(RoomBase::PLAYING_FIELD[15][15]);
}

Apple::~Apple()
{
    emit signal_die(this);
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
