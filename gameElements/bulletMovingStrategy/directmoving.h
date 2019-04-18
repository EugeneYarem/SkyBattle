#ifndef DIRECTMOVING_H
#define DIRECTMOVING_H

#include "movingstrategy.h"
#include <QObject>

class DirectMoving : public QObject, public MovingStrategy
{
    Q_OBJECT

public:
    DirectMoving() = delete;
    DirectMoving(Bullet * bullet);

private:
    bool checkBarrier(const QGraphicsItem * barrier) const override;
    bool checkBorder() const override;

signals:
    void kickPlayer() const;

};

#endif // DIRECTMOVING_H
