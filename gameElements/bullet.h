#ifndef BULLET_H
#define BULLET_H

#include "collisionsoundplayable.h"
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

class MovingStrategy;
class QTimer;

class Bullet : public QObject, public QGraphicsPixmapItem, public CollisionSoundPlayable
{
    Q_OBJECT

    static int counter;

    int number;
    Bullet * relatedBullet;
    MovingStrategy * movingStrategy;
    QMediaPlayer * mPlayerDestruction = nullptr;
    QTimer * timer;

public:
    enum ConflictSide {EnemyBullet, PlayerBullet} conflictSide;

public:
    explicit Bullet(const QPixmap & pixmap, const qreal & x, const qreal & y, const QMediaContent & destructionSound, const ConflictSide & conflictSide = ConflictSide::PlayerBullet);
    ~Bullet() override;

    Bullet * getRelatedBullet() const;
    void playCollisionSound() const override;
    void setRelatedBullet(Bullet * relatedBullet);

public slots:
    void deleteObject(const QMediaPlayer::State & musicPlayerState);
    bool move();

signals:
    void destroyEnemy();
    void kickPlayer();

};

#endif // BULLET_H
