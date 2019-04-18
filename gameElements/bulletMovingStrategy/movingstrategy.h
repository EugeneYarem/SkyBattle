#ifndef MOVINGSTRATEGY_H
#define MOVINGSTRATEGY_H

class Bullet;
class CollisionSoundPlayable;
class QGraphicsItem;

class MovingStrategy
{

protected:
    Bullet * bullet;
    double step;

public:
    MovingStrategy() = delete;
    MovingStrategy(Bullet * bullet, const double & stepSize);
    virtual ~MovingStrategy() = default;

    bool move() const;

private:
    virtual bool checkBarrier(const QGraphicsItem * barrier) const = 0;
    virtual bool checkBorder() const = 0;

protected:
    void playSoundAndRemove(const CollisionSoundPlayable * item) const;

};

#endif // MOVINGSTRATEGY_H
