#ifndef NIGHTGECREATOR_H
#define NIGHTGECREATOR_H

#include "gameelementscreator.h"

class NightGECreator : public GameElementsCreator
{

public:
    NightGECreator();

    Bullet * createEnemyBullet(const qreal & x, const qreal & y) const override;
    Bullet * createPlayerBullet(const qreal & x, const qreal & y) const override;
    Enemy * createEnemy() const override;
    Player * createPlayer() const override;
};

#endif // NIGHTGECREATOR_H
