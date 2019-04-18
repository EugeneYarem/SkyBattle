#include "directmoving.h"
#include "gameElements/bullet.h"
#include "gameElements/player.h"
#include <QGraphicsScene>

DirectMoving::DirectMoving(Bullet * bullet) : QObject(), MovingStrategy(bullet, 10)
{}

bool DirectMoving::checkBarrier(const QGraphicsItem * barrier) const
{
    if(typeid(*barrier) == typeid(Player))
    {
        if(dynamic_cast<CollisionSoundPlayable *>(const_cast<QGraphicsItem *>(barrier)))
            playSoundAndRemove(dynamic_cast<CollisionSoundPlayable *>(const_cast<QGraphicsItem *>(barrier)));
        emit kickPlayer();
        return true; // QGraphicsItem * barrier is barrier
    }
    return false;
}

bool DirectMoving::checkBorder() const
{
    if(bullet->y() > bullet->scene()->height())
    {
        bullet->scene()->removeItem(bullet);
        return true;
    }
    return false;
}
