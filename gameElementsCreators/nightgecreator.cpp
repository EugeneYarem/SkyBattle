#include "gameElements/bullet.h"
#include "gameElements/enemy.h"
#include "gameElements/player.h"
#include "nightgecreator.h"

using GEC = GameElementsCreator;

NightGECreator::NightGECreator() : GameElementsCreator(QPixmap(":/sprites/night/enemyBullet.png"),
                                                       QPixmap(":/sprites/night/enemy.png"),
                                                       QPixmap(":/sprites/night/bullet.png"),
                                                       QPixmap(":/sprites/night/player.png"), "night", Qt::yellow, Qt::white)
{}

Bullet * NightGECreator::createEnemyBullet(const qreal & x, const qreal & y) const
{
    return new Bullet(enemyBulletSprite, x - enemyBulletSprite.width() / 2, y, bulletCollisionSound, Bullet::ConflictSide::EnemyBullet);
}

Bullet * NightGECreator::createPlayerBullet(const qreal & x, const qreal & y) const
{
    return new Bullet(playerBulletSprite, x, y, bulletCollisionSound);
}

Enemy * NightGECreator::createEnemy() const
{
    return dynamic_cast<Enemy *>(enemyPrototype->clone());
}

Player * NightGECreator::createPlayer() const
{
    return dynamic_cast<Player *>(playerPrototype->clone());
}





