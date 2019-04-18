#include "bullet.h"
#include "enemy.h"
#include "gameElementsCreators/gameelementscreator.h"
#include "player.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

int Enemy::counter = 0;

Enemy::Enemy() : QObject(), Warplane()
{
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(40);// 60

    number = counter++;
}

Enemy::Enemy(const QPixmap & sprite, const QMediaContent & shutSound, const QMediaContent & destructionSound) : Enemy()
{
    setPixmap(sprite);
    setPos(rand() % 700, - this->pixmap().height());

    mPlayerShut = new QMediaPlayer();
    mPlayerShut->setMedia(shutSound);
    mPlayerShut->setVolume(90);

    mPlayerDestruction = new QMediaPlayer();
    mPlayerDestruction->setMedia(destructionSound);
    mPlayerDestruction->setVolume(40);

    connect(mPlayerDestruction, &QMediaPlayer::stateChanged, this, &Enemy::deleteObject);
}

Enemy::Enemy(const Enemy * prototype) : Enemy(prototype->pixmap(),
                                              prototype->mPlayerShut->currentMedia(),
                                              prototype->mPlayerDestruction->currentMedia())
{}

Enemy::~Enemy()
{
    delete timer;
    qDebug() << "Enemy " << number << " have been destroyed \t(" << number << "/" << Enemy::counter << ")";
}

void Enemy::createBullet() const
{
    Bullet * bullet = GameElementsCreator::getInstance().createEnemyBullet(x() + pixmap().width() / 2, y() + pixmap().height());
    bullet->setRelatedBullet(nullptr);

    connect(bullet, &Bullet::kickPlayer, this, &Enemy::kickPlayerByBullet);

    mPlayerShut->play();
    scene()->addItem(bullet);
    bullet->move();
}

void Enemy::stopMovingTimer()
{
    timer->stop();
}

Warplane * Enemy::clone() const
{
    return new Enemy(this);
}

void Enemy::move(const Direction & direction)
{
    Q_UNUSED(direction);

    setPos(x(), pos().y() + 10);

    QList<QGraphicsItem *> collidingItemsList = this->collidingItems();
    for(int i = 0, n = collidingItemsList.size(); i < n; i++)
        if(typeid(*collidingItemsList.at(i)) == typeid(Player))
        {
            mPlayerDestruction->play();
            timer->stop();
            scene()->removeItem(this);
            emit kickPlayerByYourself();
            return;
        }

    if(pos().y() > this->scene()->height())
    {
        scene()->removeItem(this);
        delete this;
        return;
    }
}

void Enemy::deleteObject(const QMediaPlayer::State & state)
{
    this->hide();
    this->setPos(-pixmap().width(), y());
    if(state == QMediaPlayer::StoppedState)
        delete this;
}
