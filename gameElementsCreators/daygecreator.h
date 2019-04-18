#ifndef DAYGECREATOR_H
#define DAYGECREATOR_H

#include "gameelementscreator.h"

class DayGECreator : public GameElementsCreator
{

public:
    DayGECreator();

    Bullet * createEnemyBullet(const qreal & x, const qreal & y) const override;
    Bullet * createPlayerBullet(const qreal & x, const qreal & y) const override;
    Enemy * createEnemy() const override;
    Player * createPlayer() const override;
};

#endif // DAYGECREATOR_H
