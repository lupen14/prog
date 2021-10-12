#ifndef PORTAL_H
#define PORTAL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QTimer>

class Portal : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Portal(QObject *parent = nullptr);

private slots:
    // анимация портала
    void slot_timer();

private:
    // физическое расположение обьекта
    QRectF boundingRect() const;

    // рисуем обьект
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void initTimer();

    // столкновение с другими обьектами
    bool collision();

    QRect   m_size;
    QTimer  *m_timerAnimation;

signals:
    void s_coincidence();
};

#endif // PORTAL_H
