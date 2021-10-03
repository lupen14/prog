#ifndef DOT_H
#define DOT_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Dot : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Dot(QObject *parent = 0);
    ~Dot();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

    static const int TYPE = 116;

private:
    QRect dotSize;
};

#endif // DOT_H
