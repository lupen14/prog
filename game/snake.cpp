#include "snake.h"
#include "roomBase.h"

#include "QDebug"

using namespace Helper;

Snake::Snake(QObject *parent) :
    QObject(parent),
    QGraphicsItem(),
    snakeSize(-16, -16, 16, 16)
{
    this->setRotation(0);
    this->setPos(RoomBase::PLAYING_FIELD[16][16]);
}

Snake::~Snake()
{

}

void Snake::gameOver()
{
    //emit signal_gameOver();
}

QRectF Snake::boundingRect() const
{
    return snakeSize;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        QPolygon polygon(snakeSize);
        painter->setBrush(Qt::red);
        painter->drawPolygon(polygon);

        Q_UNUSED(option); Q_UNUSED(widget);
}

void Snake::slotGameTimer()
{
    lastPos.clear();
    lastPos.append(QPointF(this->x(),this->y()));
    for (int i = 0; i < dots.count(); ++i) {
        lastPos.append(QPointF(dots.at(i)->x(), dots.at(i)->y()));
    }

    drivingDirections();

    move();

    checkWall();

    for (int i = 0; i < dots.count(); ++i) {
        dots.at(i)->setPos(lastPos.at(i));
    }

    collision();
}

void Snake::drivingDirections()
{
    if(GetAsyncKeyState(VK_LEFT)){
        if (directionHead != DIRECTION::RIGHT)
            directionHead = DIRECTION::LEFT;
    }
    if(GetAsyncKeyState(VK_RIGHT)){
        if (directionHead != DIRECTION::LEFT)
            directionHead = DIRECTION::RIGHT;
    }
    if(GetAsyncKeyState(VK_UP)){
        if (directionHead != DIRECTION::DOWN)
            directionHead = DIRECTION::UP;
    }
    if(GetAsyncKeyState(VK_DOWN)){
        if (directionHead != DIRECTION::UP)
            directionHead = DIRECTION::DOWN;
    }
}

void Snake::move()
{
    switch (directionHead) {
        case DIRECTION::DOWN:
        {
            this->setPos(mapToParent(0, FIELD_SIZE));
            break;
        }
        case DIRECTION::UP:
        {
            this->setPos(mapToParent(0, -FIELD_SIZE));
            break;
        }
        case DIRECTION::LEFT:
        {
            this->setPos(mapToParent(-FIELD_SIZE, 0));
            break;
        }
        case DIRECTION::RIGHT:
        {
            this->setPos(mapToParent(FIELD_SIZE, 0));
            break;
        }
    }
}

void Snake::checkWall()
{
    if(this->x() - FIELD_SIZE < BORDER_MIN_X){
        gameOver();
        this->setX(BORDER_MIN_X + FIELD_SIZE);  // слева
    }
    if(this->x() + FIELD_SIZE > BORDER_MAX_X){
        gameOver();
        this->setX(BORDER_MAX_X);               // справа
    }
    if(this->y() - FIELD_SIZE < BORDER_MIN_Y){
        gameOver();
        this->setY(BORDER_MIN_Y + FIELD_SIZE);  // сверху
    }
    if(this->y() + FIELD_SIZE > BORDER_MAX_Y){
        gameOver();
        this->setY(BORDER_MAX_Y);               // снизу
    }
}

void Snake::collision()
{
    QList<QGraphicsItem *> list = this->collidingItems();
    foreach(QGraphicsItem *item , list)
    {
        switch (item->type()) {
            case Apple::TYPE:
            {
                this->scene()->removeItem(item);
                delete item;

                addDot();

                break;
            }
            case Dot::TYPE:
            {
                /// удаляем тело до тех пор пока не удлим с тем с котом столкнулись
                while ( dots.lastIndexOf(item) > 0 )
                {
                    this->scene()->removeItem(dots.last());
                    dots.removeOne(dots.last());
                    delete dots.last();
                    dots.removeAt(dots.indexOf(dots.last()));
                }
                break;
            }
        }
    }
}

void Snake::addDot()
{
    Dot *dot = new Dot();
    this->scene()->addItem(dot);
    dot->setPos(lastPos.last());
    dots.append(dot);
}
