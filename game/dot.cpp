#include "dot.h"
#include "mainwindow.h"

#include "QDateTime"
#include <QDebug>

int Dot::s_count = 0;

const QString Dot::s_imageDirectBase    = ":snake/images/snake/dot_direct_base.png";
const QString Dot::s_imageAngleBase     = ":snake/images/snake/dot_angle_base.png";
const QString Dot::s_imageTailBase      = ":snake/images/snake/dot_tail_base.png";
const QString Dot::s_imageDirectSpeed   = ":snake/images/snake/dot_direct_speed.png";
const QString Dot::s_imageAngleSpeed    = ":snake/images/snake/dot_angle_speed.png";
const QString Dot::s_imageTailSpeed     = ":snake/images/snake/dot_tail_speed.png";

Dot::Dot(QGraphicsItem *__frontItem, QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    m_type(static_cast<itemType>(ItemType::DOT)),
    m_size(-8, -8, 16, 16),
    m_frontItem(__frontItem),
    m_dotDirect(s_imageDirectBase),
    m_dotAngle(s_imageAngleBase),
    m_dotTail(s_imageTailBase)
{
    m_number = ++s_count;
    setRotation(Angle::ANGLE_0);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    this->setZValue(ItemZValue::Z_SNAKE);
}

Dot::~Dot()
{
    --s_count;
    emit signal_setSnakeSpeed(-1);
}

void Dot::setMutagenNone()
{
    m_mutagen = Mutagen::NONE;

    m_dotDirect = s_imageDirectBase;
    m_dotAngle  = s_imageAngleBase;
    m_dotTail   = s_imageTailBase;
}

void Dot::setMutagenSpeed()
{
    m_mutagen = Mutagen::SPEED;

    m_dotDirect = s_imageDirectSpeed;
    m_dotAngle  = s_imageAngleSpeed;
    m_dotTail   = s_imageTailSpeed;

    emit signal_setSnakeSpeed(1);
}


QRectF Dot::boundingRect() const
{
    return m_size;
}

void Dot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (s_count == m_number)
    {
        m_currDotPixmap.load(m_dotTail);
    }

    painter->drawPixmap(m_size, m_currDotPixmap);

    Q_UNUSED(option); Q_UNUSED(widget);
}

itemType Dot::type() const
{
    return m_type;
}

void Dot::printBload()
{
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap(":snake/images/snake/snake_blood.png"));
    scene()->addItem(item);
    item->setZValue(ItemZValue::Z_BACKGROUND);
    item->setPos(pos().x() - 8, pos().y() - 8);
}

QVariant Dot::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        QPointF prevPosItem(this->pos());
        QPointF currPosItem(value.toPointF());
        QPointF nextPosItem(m_frontItem->pos());

        m_currDotPixmap.load(m_dotDirect);

        if (currPosItem.x() == nextPosItem.x()) /// тело идет по горезонтали вслед за следующим телом
        {
            if (currPosItem.y() > nextPosItem.y())
                this->setRotation(Angle::ANGLE_270); /// тело двигается вниз за своим следующим телом
            else
                this->setRotation(Angle::ANGLE_90); /// тело двигается вверх за своим следующим телом

            if (s_count == m_number) /// если это хвост, то дальнейшие действия не нужны
                return QGraphicsItem::itemChange(change, value);


            if (prevPosItem.y() == currPosItem.y() && prevPosItem.x() != currPosItem.x()) /// если поумали тело на углу
            {
                m_currDotPixmap.load(m_dotAngle);

                if (currPosItem.y() > nextPosItem.y())
                { /// тело двигается вниз
                    if (currPosItem.x() > prevPosItem.x())
                        this->setRotation(Angle::ANGLE_180); /// повернули налево идя вниз
                    else
                        this->setRotation(Angle::ANGLE_270); /// повернули направа идя вниз
                }
                else
                { /// тело двигается вверх
                    if (currPosItem.x() > prevPosItem.x())
                        this->setRotation(Angle::ANGLE_90); /// повернули направа идя вверх
                    else
                        this->setRotation(Angle::ANGLE_0); /// повернули налево идя вверх
                }
            }
        }

        if (currPosItem.y() == nextPosItem.y()) /// тело идет по вертикали вслед за следующим телом
        {
            if (currPosItem.x() > nextPosItem.x())
                this->setRotation(Angle::ANGLE_180);  /// тело двигается влева за своим следующим телом
            else
                this->setRotation(Angle::ANGLE_0);  /// тело двигается вправа за своим следующим телом

            if (s_count == m_number) /// если это хвост, то дальнейшие действия не нужны
                return QGraphicsItem::itemChange(change, value);

            if (prevPosItem.x() == currPosItem.x() && prevPosItem.y() != currPosItem.y()) /// если поумали тело на углу
            {
                m_currDotPixmap.load(m_dotAngle);

                if (currPosItem.x() > nextPosItem.x())
                {   /// тело двигается вправа
                    if (currPosItem.y() > prevPosItem.y())
                        this->setRotation(Angle::ANGLE_180); /// повернули вверх идя вправа
                    else
                        this->setRotation(Angle::ANGLE_90); /// повернули вниз идя вправа
                }
                else /// тело двигается налево
                {
                    if (currPosItem.y() > prevPosItem.y())
                        this->setRotation(Angle::ANGLE_270); /// повернули вверх идя налево
                    else
                        this->setRotation(Angle::ANGLE_0); /// повернули вниз идя налево
                }
            }
        }
    }

    return QGraphicsItem::itemChange(change, value);
}
