#ifndef DOT_H
#define DOT_H


#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Dot : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Dot(QGraphicsItem *__frontItem, QObject *parent = 0);
    ~Dot();

    int type() const;

    static const int TYPE = 116;
    static int s_count;
    static QString s_dotDirect;
    static QString s_dotAngle;
    static QString s_dotTail;
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
};

#endif // DOT_H
