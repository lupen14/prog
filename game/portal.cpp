#include "portal.h"

#include "Helper.h"

#include <QDateTime>

#include "QDebug"

using namespace Helper;

Portal::Portal(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    m_size(-16, -16, 32, 32)
{
    initTimer();
    this->setZValue(ItemZValue::Z_PORTAL);
}

QRectF Portal::boundingRect() const
{
    return m_size;
}

void Portal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static bool paint = true;
    if (true == paint)
    {
        painter->drawPixmap(m_size, QPixmap(":portal/images/portal/portal 1-1.png"));
        paint = false;
    }
    else
    {
        painter->drawPixmap(m_size, QPixmap(":portal/images/portal/portal 1-2.png"));
        paint = true;
    }

    Q_UNUSED(option); Q_UNUSED(widget);
}

void Portal::initTimer()
{
    m_timerAnimation = new QTimer();
    connect(m_timerAnimation, &QTimer::timeout, this, &Portal::slot_timer);
    m_timerAnimation->start(1000 / 6);
}

void Portal::slot_timer()
{
    this->update();

    if (true == collision())
    {
        emit s_coincidence();
    }
}

bool Portal::collision()
{
    QList<QGraphicsItem *> list = this->collidingItems();
    foreach(QGraphicsItem *item , list)
    {
        switch (item->type()) {
            case static_cast<itemType>(ItemType::SNAKE):
            {
                return true;
                break;
            }
        }
    }

    return false;
}
