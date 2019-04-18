#ifndef PLAYER_H
#define PLAYER_H

#include "warplane.h"

class QTime;

class Player : public QObject, public Warplane
{
    Q_OBJECT

    QTime * timeOfLastBullet;

public:
    Player(const QPixmap & sprite, const QMediaContent & shutSound, const QMediaContent & destructionSound);
    Player(const Player * prototype);
    ~Player() override;

    void createBullet() const override;
    void keyPressEvent(QKeyEvent * event) override;
    void move(const Direction & direction) override;
    Warplane * clone() const override;

private:
    Player();

signals:
    void destroyEnemy();

};

#endif // PLAYER_H
