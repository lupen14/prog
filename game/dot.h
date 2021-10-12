#ifndef DOT_H
#define DOT_H

#include "Helper.h"

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

using namespace Helper;

class Dot : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Dot(QGraphicsItem *__frontItem, QObject *parent = 0);
    ~Dot();

    static const QString s_imageDirectSpeed;
    static const QString s_imageAngleSpeed;
    static const QString s_imageTailSpeed;
    static const QString s_imageDirectBase;
    static const QString s_imageAngleBase;
    static const QString s_imageTailBase;

    static const typeItem TYPE = static_cast<typeItem>(ItemType::DOT);
    static typeItem s_count;
    typeItem type() const;

    void printBload();

    Mutagen getMutagen();
    void setMutagenNone();
    void setMutagenSpeed();


signals:
    void signal_setSnakeSpeed(snakeSpeed __speed);

private:
    // вызывается на изменение обьекта
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    // физическое расположение обьекта
    QRectF boundingRect() const;

    // рисуем обьект
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRect           m_size;
    QGraphicsItem  *m_frontItem;
    QPixmap         m_currDotPixmap;
    int             m_number;
    Mutagen         m_mutagen;
    QString         m_dotDirect;
    QString         m_dotAngle;
    QString         m_dotTail;
};

#endif // DOT_H
