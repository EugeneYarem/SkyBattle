#include "gameElements/bullet.h"
#include "gameElements/enemy.h"
#include "reversemoving.h"
#include <QGraphicsScene>

ReverseMoving::ReverseMoving(Bullet * bullet) : QObject(), MovingStrategy(bullet, -10)
{}

bool ReverseMoving::checkBarrier(const QGraphicsItem * barrier) const
{
    if(typeid(*barrier) == typeid(Enemy))
    {
        if(dynamic_cast<CollisionSoundPlayable *>(const_cast<QGraphicsItem *>(barrier)))
            playSoundAndRemove(dynamic_cast<CollisionSoundPlayable *>(const_cast<QGraphicsItem *>(barrier)));
        emit destroyEnemy();
        return true; // QGraphicsItem * barrier is barrier
    }
    return false;
}

bool ReverseMoving::checkBorder() const
{
    if(bullet->y() < -bullet->pixmap().height())
    {
        bullet->scene()->removeItem(bullet);
        return true;
    }
    return false;
}


