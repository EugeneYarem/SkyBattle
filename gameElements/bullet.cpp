#include "bulletMovingStrategy/directmoving.h"
#include "bulletMovingStrategy/reversemoving.h"
#include "bullet.h"
#include "enemy.h"
#include "health.h"
#include "player.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QList>
#include <QTimer>

int Bullet::counter = 0;

Bullet::Bullet(const QPixmap & pixmap, const qreal & x, const qreal & y, const QMediaContent & destructionSound, const ConflictSide & conflictSide) : QObject()
{
    if(conflictSide == ConflictSide::EnemyBullet)
    {
        movingStrategy = new DirectMoving(this);
        connect(dynamic_cast<DirectMoving *>(movingStrategy), &DirectMoving::kickPlayer, this, &Bullet::kickPlayer);
    }
    else
    {
        movingStrategy = new ReverseMoving(this);
        connect(dynamic_cast<ReverseMoving *>(movingStrategy), &ReverseMoving::destroyEnemy, this, &Bullet::destroyEnemy);
    }

    setPixmap(pixmap);
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    this->conflictSide = conflictSide;

    setPos(x, y);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    mPlayerDestruction = new QMediaPlayer();
    mPlayerDestruction->setMedia(destructionSound);
    mPlayerDestruction->setVolume(100);
    connect(mPlayerDestruction, &QMediaPlayer::stateChanged, this, &Bullet::deleteObject);

    number = counter++;
}

Bullet::~Bullet()
{
    delete movingStrategy;
    delete mPlayerDestruction;
    delete timer;
    qDebug() << "Bullet " << number << " have been destroyed \t(" << number << "/" << Bullet::counter << ")";
}

bool Bullet::move()
{
    timer->stop();

    if(movingStrategy->move())
    {
        timer->start(25);
        return true;
    }
    else
    {
        delete this;
        return false;
    }
}

void Bullet::deleteObject(const QMediaPlayer::State & state)
{
    this->hide();
    this->setPos(scene()->width() + 10, y());
    if(state == QMediaPlayer::StoppedState)
        delete this;
}

void Bullet::setRelatedBullet(Bullet * bullet)
{
    relatedBullet = bullet;
}

Bullet * Bullet::getRelatedBullet() const
{
    return relatedBullet;
}

void Bullet::playCollisionSound() const
{
    mPlayerDestruction->play();
}
