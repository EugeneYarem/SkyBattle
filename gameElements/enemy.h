#ifndef ENEMY_H
#define ENEMY_H

#include "warplane.h"
#include <QObject>

class QTimer;

class Enemy : public QObject, public Warplane
{
    Q_OBJECT

    static int counter;

    int number;

    QTimer * timer;

public:
    Enemy(const QPixmap & sprite, const QMediaContent & shutSound, const QMediaContent & destructionSound);
    Enemy(const Enemy * prototype);
    ~Enemy() override;

    void createBullet() const override;
    void stopMovingTimer();
    Warplane * clone() const override;

private:
    Enemy();

public slots:
    void deleteObject(const QMediaPlayer::State & musicPlayerState);
    void move(const Direction & direction = Direction::Left) override; // direction isn't used in implementation of function, but it needs default value for compatibility with signal

signals:
    void kickPlayerByBullet();
    void kickPlayerByYourself();

};

#endif // ENEMY_H
