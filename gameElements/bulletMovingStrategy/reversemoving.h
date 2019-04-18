#ifndef REVERSEMOVING_H
#define REVERSEMOVING_H

#include "movingstrategy.h"
#include <QObject>

class ReverseMoving : public QObject, public MovingStrategy
{
    Q_OBJECT

public:
    ReverseMoving() = delete;
    ReverseMoving(Bullet * bullet);

private:
    bool checkBarrier(const QGraphicsItem * barrier) const override;
    bool checkBorder() const override;

signals:
    void destroyEnemy() const;

};

#endif // REVERSEMOVING_H
