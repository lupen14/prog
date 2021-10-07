#ifndef APPLE_H
#define APPLE_H

#include "Helper.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>

class Apple : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Apple(const AppleFlags::Flags &__flag);
    ~Apple();

    // разбираем флаг у яблочка
    void parsingFlag(const AppleFlags::Flags &__flag);

    // наделяем яблоко свойствами
    void configuringApple();

    // физическое расположение обьекта
    QRectF boundingRect() const;

    // рисуем обьект
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // возвращаем тип обьекта, чтобы его идентифицировать
    int type() const;

    static const int TYPE = 5;

signals:
    void signal_die(Apple*);

private slots:
    void slot_appleTimer();

private:
    // оживляем яблоко
    void initTimer();

    // проверка преград перед перемещеним
    bool checkObstacles(const Movement::Direction &__direction);

    // движение яблока
    void move(const Movement::Direction &__direction);

    QTimer  *m_timer;
    QRect   m_size;
    bool    m_move;
    int     m_appleSpeed;
};

#endif // APPLE_H
