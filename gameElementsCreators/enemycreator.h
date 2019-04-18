#ifndef ENEMYCREATOR_H
#define ENEMYCREATOR_H

#include <QObject>

class QGraphicsScene;
class QTimer;

class EnemyCreator : public QObject
{
    Q_OBJECT

    QGraphicsScene * scene;
    QTimer * timerCreate;

public:
    explicit EnemyCreator(QGraphicsScene * scene);
    ~EnemyCreator();

public slots:
    void spawn() const;

signals:
    void kickPlayerByBullet();
    void kickPlayerByYourself();

};

#endif // ENEMYCREATOR_H
