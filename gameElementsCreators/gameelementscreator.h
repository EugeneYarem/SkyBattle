#ifndef GAMEELEMENTSCREATOR_H
#define GAMEELEMENTSCREATOR_H

#include <QColor>
#include <QMediaContent>
#include <QPixmap>
#include <QString>

class Bullet;
class Enemy;
class Player;

class GameElementsCreator
{
    static GameElementsCreator * instance;

protected:
//-------- Sounds (must be loaded before the prototypes)
    QMediaContent bulletCollisionSound = QUrl("qrc:/sounds/clap.mp3");
    QMediaContent enemyShutSound = QUrl("qrc:/sounds/enemyShut.mp3");
    QMediaContent explosionSound = QUrl("qrc:/sounds/explosion.mp3");
    QMediaContent gameOverSound = QUrl("qrc:/sounds/gameOver.mp3");
    QMediaContent hitSound = QUrl("qrc:/sounds/hit.mp3");
    QMediaContent playerShutSound = QUrl("qrc:/sounds/playerShut.mp3");

//-------- Prototypes
    Bullet * enemyBulletPrototype;
    Bullet * playerBulletPrototype;
    Enemy * enemyPrototype;
    Player * playerPrototype;

//-------- Sprites
    QPixmap enemyBulletSprite;
    QPixmap enemySprite;
    QPixmap playerBulletSprite;
    QPixmap playerSprite;

//-------- Colors
    QColor healthColor;
    QColor scoreColor;

    QString imgPrefix;

public:
    GameElementsCreator() = default;
    GameElementsCreator(QPixmap enemyBulletSprite, QPixmap enemySprite,
                        QPixmap playerBulletSprite, QPixmap playerSprite,
                        QString imgPrefix, QColor health, QColor score);
    virtual ~GameElementsCreator();

    static void initialise(GameElementsCreator * creator);
    static GameElementsCreator & getInstance();

    QColor getHealthColor();
    QColor getScoreColor();

    virtual Bullet * createEnemyBullet(const qreal & x, const qreal & y) const = 0;
    virtual Bullet * createPlayerBullet(const qreal & x, const qreal & y) const = 0;
    virtual Enemy * createEnemy() const = 0;
    virtual Player * createPlayer() const = 0;

};

#endif // GAMEELEMENTSCREATOR_H
