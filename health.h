#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QObject>

class Health : public QGraphicsTextItem
{
    Q_OBJECT

    int health = 5;

public:
    Health();

    void decrease();

signals:
    void playerHaveBeenDestroyed();

};

#endif // HEALTH_H
