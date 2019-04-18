#include "bullet.h"
#include "gameElementsCreators/gameelementscreator.h"
#include "player.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QRectF>
#include <QTime>

Player::Player() : QObject()
{   
    setCacheMode(QGraphicsItem::DeviceCoordinateCache);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    timeOfLastBullet = new QTime();
    timeOfLastBullet->start();
}

Player::Player(const QPixmap & sprite, const QMediaContent & shutSound, const QMediaContent & destructionSound) : Player()
{
    setPixmap(sprite);

    mPlayerShut = new QMediaPlayer();
    mPlayerShut->setMedia(shutSound);
    mPlayerShut->setVolume(90);

    mPlayerDestruction = new QMediaPlayer();
    mPlayerDestruction->setMedia(destructionSound);
    mPlayerDestruction->setVolume(60);
}

Player::Player(const Player * prototype) : Player(prototype->pixmap(),
                                                  prototype->mPlayerShut->currentMedia(),
                                                  prototype->mPlayerDestruction->currentMedia())
{}

Player::~Player()
{
    delete timeOfLastBullet;
    qDebug() << "Player has been destroyed";
}

void Player::createBullet() const
{
    if (timeOfLastBullet->elapsed() < 1000)
        return;

    Bullet * bullet1 = GameElementsCreator::getInstance().createPlayerBullet(x(), y());
    Bullet * bullet2 = GameElementsCreator::getInstance().createPlayerBullet(x() + this->pixmap().width() - bullet1->pixmap().width(), y());

    connect(bullet1, &Bullet::destroyEnemy, this, &Player::destroyEnemy);
    connect(bullet2, &Bullet::destroyEnemy, this, &Player::destroyEnemy);

    mPlayerShut->stop();
    mPlayerShut->play();
    scene()->addItem(bullet1);
    scene()->addItem(bullet2);

    bullet1->setRelatedBullet(bullet2);
    bullet2->setRelatedBullet(bullet1);

    bullet1->move();
    if(bullet1->getRelatedBullet())
        bullet2->move();

    timeOfLastBullet->restart();
}

void Player::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Left)
    {
        move(Direction::Left);
        return;
    }
    if(event->key() == Qt::Key_Right)
    {
        move(Direction::Right);
        return;
    }
    if(event->key() == Qt::Key_Space && !event->isAutoRepeat())
    {
        createBullet();
    }
}

void Player::move(const Warplane::Direction & direction)
{
    if(direction == Direction::Left && x() > 0)
    {
        if(x() >= 15)
            this->setPos(pos().x() - this->pixmap().width() / 2, y());
        else this->setPos(0, y());
        return;
    }
    if(direction == Direction::Right && x() < scene()->width() - pixmap().width())
    {
        if(scene()->width() - x() - pixmap().width() >= 15)
            this->setPos(pos().x() + 15, y());
        else this->setPos(pos().x() + scene()->width() - x() - pixmap().width(), y());
        return;
    }
}

Warplane * Player::clone() const
{
    return new Player(this);
}
