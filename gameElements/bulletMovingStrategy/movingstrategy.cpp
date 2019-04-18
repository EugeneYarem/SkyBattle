#include "gameElements/bullet.h"
#include "movingstrategy.h"
#include "gameElements/player.h"
#include <QGraphicsScene>

MovingStrategy::MovingStrategy(Bullet * bullet, const double & stepSize) : bullet(bullet), step(stepSize)
{}

bool MovingStrategy::move() const
{
    bullet->setPos(bullet->x(), bullet->y() + step);

    QList<QGraphicsItem *> collidingItemsList = bullet->collidingItems();
    for(int i = 0, n = collidingItemsList.size(); i < n; i++)
    {
        if(bullet->getRelatedBullet() != nullptr)
        {
            qreal xAB = bullet->getRelatedBullet()->x(),
            widthAB = bullet->getRelatedBullet()->pixmap().width(),
            xE = collidingItemsList.at(i)->pos().x(),
            widthE = collidingItemsList[i]->boundingRect().width();
            if( ((xAB + widthAB > xE && xAB < xE) || (xAB < xE + widthE && xAB > xE)) )
            {
                bullet->scene()->removeItem(bullet->getRelatedBullet());
                delete bullet->getRelatedBullet();
                bullet->setRelatedBullet(nullptr);
            }
            else bullet->getRelatedBullet()->setRelatedBullet(nullptr);
        }

        if(typeid(*collidingItemsList.at(i)) == typeid(Bullet))
        {
            Bullet * temp = static_cast<Bullet *>(collidingItemsList.at(i));
            if(temp->getRelatedBullet() != nullptr)
                temp->getRelatedBullet()->setRelatedBullet(nullptr);
            playSoundAndRemove(dynamic_cast<CollisionSoundPlayable *>(collidingItemsList.at(i)));
            return false;
        }

        return !checkBarrier(collidingItemsList.at(i));
    }

    return !checkBorder();
}

void MovingStrategy::playSoundAndRemove(const CollisionSoundPlayable * item) const
{
    item->playCollisionSound();
    bullet->scene()->removeItem(bullet);
}
