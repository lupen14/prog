#include "apple.h"
#include "roomBase.h"

#include "QDebug"

using namespace Helper;

Apple::Apple(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    appleSize(-16, -16, 16, 16)
{
    setRotation(0);
    srand(static_cast<unsigned int>(time(0)));
    setPos(RoomBase::PLAYING_FIELD[rand()%FIELD_SIZE_X][rand()%FIELD_SIZE_Y]);
}

Apple::~Apple()
{
    emit signal_die(this);
}

QRectF Apple::boundingRect() const
{
    return appleSize;
}

void Apple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon(appleSize);
    painter->setBrush(Qt::green);
    painter->drawPolygon(polygon);

    Q_UNUSED(option); Q_UNUSED(widget);
}

int Apple::type() const
{
    return TYPE;
}
