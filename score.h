#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
    int score = 0;

public:
    Score();

    void increase();
    int getScore() const;

};

#endif // SCORE_H
