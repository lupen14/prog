#ifndef APPLE_H
#define APPLE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Apple : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Apple(QObject *parent = 0);
    ~Apple();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;

    static const int TYPE = 5;

signals:
   void signal_die(Apple*);

private:
   QRect appleSize;

};

#endif // APPLE_H
