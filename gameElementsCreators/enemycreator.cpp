#include "enemycreator.h"
#include "health.h"
#include "gameElements/enemy.h"
#include "gameElementsCreators/gameelementscreator.h"
#include "score.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>

EnemyCreator::EnemyCreator(QGraphicsScene * scene) : QObject()
{
    this->scene = scene;
    timerCreate = new QTimer();
    connect(timerCreate, SIGNAL(timeout()), this, SLOT(spawn()));
    timerCreate->start(1000/*1150*/);
}

EnemyCreator::~EnemyCreator()
{
    delete timerCreate;
}

void EnemyCreator::spawn() const
{
    Enemy * enemy = GameElementsCreator::getInstance().createEnemy();
    connect(enemy, &Enemy::kickPlayerByBullet, this, &EnemyCreator::kickPlayerByBullet);
    connect(enemy, &Enemy::kickPlayerByYourself, this, &EnemyCreator::kickPlayerByYourself);
    scene->addItem(enemy);
    QList<QGraphicsItem *> collidingItemsList = enemy->collidingItems();
    if(collidingItemsList.size() == 0 || typeid(*collidingItemsList.at(0)) == typeid(Health) || typeid(*collidingItemsList.at(0)) == typeid(Score))
        enemy->createBullet();
}
