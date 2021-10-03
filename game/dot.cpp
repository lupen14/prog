#include "dot.h"
#include "mainwindow.h"

Dot::Dot(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    dotSize(-16, -16, 16, 16)
{
    setRotation(0);
}

Dot::~Dot()
{
}

QRectF Dot::boundingRect() const
{
    return dotSize;
}

void Dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon polygon(dotSize);
    painter->setBrush(Qt::yellow);
    painter->drawPolygon(polygon);

    Q_UNUSED(option); Q_UNUSED(widget);
}

int Dot::type() const
{
    return TYPE;
}
