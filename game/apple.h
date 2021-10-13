#ifndef APPLE_H
#define APPLE_H

#include "Helper.h"

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>

using namespace Base;
using namespace Helper;

class Apple : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    Apple(const QGraphicsScene *__scene);
    ~Apple();

    // физическое расположение обьекта
    QRectF boundingRect() const;

    // рисуем обьект
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // говорим яблоку, что оно должно двигаться
    void setMove(const bool& __move);
    inline bool getMove();

    // наделяют яблоко мутагеном
    void setMutagen(const Mutagen &__mutagen);
    void setRandomMutagen();
    Mutagen getMutagen();

    // возвращаем тип обьекта, чтобы его идентифицировать
    typeItem type() const;

    static const typeItem TYPE = static_cast<typeItem>(ItemType::APPLE);

signals:
    void signal_die(Apple*);

private slots:
    void slot_appleTimer();

private:
    //определяем позиция яблока
    void positionDetermination(const QGraphicsScene *__scene);

    // оживляем яблоко
    void initTimer();

    // оживляем яблоко
    void dieTimer();

    // проверка преград перед перемещеним
    bool checkObstacles(const Movement::Direction &__direction);

    // проверка что куда хочет переместиться яблоко есть ли другой обьект
    bool checkOutsiderItem(const int &__x, const int &__y);

    // движение яблока
    void move(const Movement::Direction &__direction);

    QTimer  *m_timer;
    QRect   m_size;
    int     m_appleSpeedMove;
    QPixmap m_pixmap;
    bool    m_move;
    Mutagen m_mutagen;
};

#endif // APPLE_H
