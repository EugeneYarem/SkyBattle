#include "health.h"
#include "gameElementsCreators/gameelementscreator.h"
#include <QFont>
#include <QGraphicsTextItem>

Health::Health()
{
    setPlainText("Здоровье: " + QString::number(health));
    setFont(QFont("Tahoma", 16));
    setDefaultTextColor(GameElementsCreator::getInstance().getHealthColor());
}

void Health::decrease()
{
    health--;
    setPlainText("Здоровье: " + QString::number(health));

    if(health == 0)
        emit playerHaveBeenDestroyed();
}
