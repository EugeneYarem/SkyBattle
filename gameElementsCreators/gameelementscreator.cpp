#include "gameElements/bullet.h"
#include "gameElements/enemy.h"
#include "gameElements/player.h"
#include "gameelementscreator.h"

GameElementsCreator * GameElementsCreator::instance = nullptr;

GameElementsCreator::GameElementsCreator(QPixmap eBS, QPixmap eS, QPixmap pBS, QPixmap pS, QString imgPrefix, QColor health, QColor score) :
    enemyBulletSprite(eBS), enemySprite(eS), playerBulletSprite(pBS), playerSprite(pS), imgPrefix(imgPrefix), healthColor(health), scoreColor(score),
    enemyBulletPrototype(new Bullet(eBS, 0, 0, bulletCollisionSound, Bullet::ConflictSide::EnemyBullet)),
    playerBulletPrototype(new Bullet(pBS, 0, 0, bulletCollisionSound, Bullet::ConflictSide::PlayerBullet)),
    enemyPrototype(new Enemy(eS, enemyShutSound, explosionSound)),
    playerPrototype(new Player(pS, playerShutSound, hitSound))
{
    enemyPrototype->stopMovingTimer();
}

GameElementsCreator::~GameElementsCreator()
{
    delete enemyBulletPrototype;
    delete playerBulletPrototype;
    delete enemyPrototype;
    delete playerPrototype;
}

void GameElementsCreator::initialise(GameElementsCreator * creator)
{
    if(!GameElementsCreator::instance)
        instance = creator;
}

GameElementsCreator & GameElementsCreator::getInstance()
{
    return *GameElementsCreator::instance;
}

QColor GameElementsCreator::getHealthColor()
{
    return healthColor;
}

QColor GameElementsCreator::getScoreColor()
{
    return scoreColor;
}
