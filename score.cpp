#include "gameElementsCreators/gameelementscreator.h"
#include "score.h"
#include <QFont>

Score::Score()
{
    setPlainText("Счёт: " + QString::number(score));
    setFont(QFont("Tahoma", 16));
    setDefaultTextColor(GameElementsCreator::getInstance().getScoreColor());
}

void Score::increase()
{
    score++;
    setPlainText("Счёт: " + QString::number(score));
}

int Score::getScore() const
{
    return score;
}
