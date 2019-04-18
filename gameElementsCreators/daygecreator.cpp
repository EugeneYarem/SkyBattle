#include "daygecreator.h"
#include "gameElements/bullet.h"
#include "gameElements/enemy.h"
#include "gameElements/player.h"

using GEC = GameElementsCreator;

DayGECreator::DayGECreator() : GameElementsCreator(QPixmap(":/sprites/day/enemyBullet.png"),
                                                       QPixmap(":/sprites/day/enemy.png"),
                                                       QPixmap(":/sprites/day/bullet.png"),
                                                       QPixmap(":/sprites/day/player.png"), "day", Qt::red, Qt::blue)
{}

Bullet * DayGECreator::createEnemyBullet(const qreal & x, const qreal & y) const
{
    return new Bullet(enemyBulletSprite, x - enemyBulletSprite.width() / 2, y, bulletCollisionSound, Bullet::ConflictSide::EnemyBullet);
}

Bullet * DayGECreator::createPlayerBullet(const qreal & x, const qreal & y) const
{
    return new Bullet(playerBulletSprite, x, y, bulletCollisionSound);
}

Enemy * DayGECreator::createEnemy() const
{
    return dynamic_cast<Enemy *>(enemyPrototype->clone());
}

Player * DayGECreator::createPlayer() const
{
    return dynamic_cast<Player *>(playerPrototype->clone());
}





