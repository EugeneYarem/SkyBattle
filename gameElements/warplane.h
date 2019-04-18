#ifndef WARPLANE_H
#define WARPLANE_H

#include "collisionsoundplayable.h"
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Warplane : public QGraphicsPixmapItem, public CollisionSoundPlayable
{

protected:
    QMediaPlayer * mPlayerShut = nullptr;
    QMediaPlayer * mPlayerDestruction = nullptr;

public:
    enum Direction {Right, Left};

public:
    Warplane() = default;
    virtual ~Warplane() override;

    virtual void createBullet() const = 0;
    virtual void move(const Direction & direction) = 0;
    virtual Warplane * clone() const = 0;
    void playCollisionSound() const override;

};

#endif // WARPLANE_H
