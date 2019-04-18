#ifndef GAME_H
#define GAME_H

#include "health.h"
#include "gameElements/enemy.h"
#include "gameElements/player.h"
#include "gameElementsCreators/enemycreator.h"
#include "score.h"
#include <QGraphicsView>
#include <QMediaPlayer>

class QGraphicsScene;
class QTimer;

class Game : public QGraphicsView
{
    Q_OBJECT

    static Game * instance;

    EnemyCreator * enemyCreator;
    Health * health;
    Player * player;
    QGraphicsScene * scene;
    QMediaPlayer * mPlayer;
    Score * score;

public:
    ~Game();
    static Game & getInstance();
    static void initialise(const QApplication * application);
    void gameOver();

private:
    explicit Game(QWidget * parent = nullptr);
    Game(Game &) = delete;
    Game(Game &&) = delete;
    Game(Game *) = delete;
    Game & operator= (Game &) = delete;
    Game & operator= (Game &&) = delete;

public slots:
    void restartMusicPlay(const QMediaPlayer::State & musicPlayerState) const;

};

#endif // GAME_H
