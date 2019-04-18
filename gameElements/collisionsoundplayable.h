#ifndef COLLISIONSOUNDPLAYABLE_H
#define COLLISIONSOUNDPLAYABLE_H

class CollisionSoundPlayable
{

public:
    virtual ~CollisionSoundPlayable() = default;
    virtual void playCollisionSound() const = 0;

};

#endif // COLLISIONSOUNDPLAYABLE_H
