#include "game.h"
#include "gameElementsCreators/gameelementscreator.h"
#include "gameElementsCreators/daygecreator.h"
#include "gameElementsCreators/nightgecreator.h"
#include <QApplication>
#include <QBrush>
#include <QImage>
#include <QGraphicsScene>
#include <QThread>
#include <QTimer>
#include <QTime>
#include <QUrl>

Game * Game::instance = nullptr;

Game::Game(QWidget * parent) : QGraphicsView (parent)
{ 
    if(QTime::currentTime().hour() >= 21 || QTime::currentTime().hour() < 5)
    {
        setBackgroundBrush(QBrush(QImage(":/sprites/night/background.png")));
        GameElementsCreator::initialise(new NightGECreator);
    }
    else
    {
        setBackgroundBrush(QBrush(QImage(":/sprites/day/background.png")));
        GameElementsCreator::initialise(new DayGECreator);
    }

    setOptimizationFlag(QGraphicsView::IndirectPainting);
    setFixedSize(800, 600);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, this->width(), this->height());
    setScene(scene);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);

    setCacheMode(QGraphicsView::CacheBackground);
    setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);

    player = GameElementsCreator::getInstance().createPlayer();
    player->setPos(width() / 2 - player->pixmap().width() / 2, height() - player->pixmap().height());
    scene->addItem(player);

    health = new Health();
    health->setPos(0, 0);
    scene->addItem(health);

    connect(health, &Health::playerHaveBeenDestroyed, this, &Game::gameOver);

    score = new Score();
    score->setPos(0, 40);
    scene->addItem(score);

    connect(player, &Player::destroyEnemy, score, &Score::increase);

    enemyCreator = new EnemyCreator(scene);
    connect(enemyCreator, &EnemyCreator::kickPlayerByBullet, health, &Health::decrease);
    connect(enemyCreator, &EnemyCreator::kickPlayerByYourself, score, &Score::increase);
    connect(enemyCreator, &EnemyCreator::kickPlayerByYourself, health, &Health::decrease);

    mPlayer = new QMediaPlayer();
    mPlayer->setMedia(QUrl("qrc:/sounds/background.mp3"));
    connect(mPlayer, &QMediaPlayer::stateChanged, this, &Game::restartMusicPlay);
    mPlayer->play();
    mPlayer->setVolume(90);

    show();
}

Game::~Game()
{
    delete enemyCreator;
    delete mPlayer;
    delete scene;
}

Game & Game::getInstance()
{
    return *instance;
}

void Game::initialise(const QApplication * application)
{
    if(!Game::instance)
    {
        instance = new Game;
        QObject::connect(application, &QApplication::aboutToQuit, instance, &Game::deleteLater);
    }
}

void Game::gameOver()
{
    static bool isExecuted = false;
    if(!isExecuted)
    {
        QFont font("Tahoma", 20);
        font.setBold(true);
        QGraphicsTextItem * gameOver = new QGraphicsTextItem("Игра окончена!\nВаш счёт: " + QString::number(score->getScore()));
        gameOver->setFont(font);
        gameOver->setDefaultTextColor(Qt::red);
        gameOver->setPos(300, 250);
        scene->clear();
        scene->addItem(gameOver);
        isExecuted = true;
    }
}

void Game::restartMusicPlay(const QMediaPlayer::State & state) const
{
    if(state == QMediaPlayer::StoppedState)
        mPlayer->play();
}
