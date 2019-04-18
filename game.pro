#-------------------------------------------------
#
# Project created by QtCreator 2017-10-25T12:03:34
#
#-------------------------------------------------

QT       += core gui \
            multimedia \
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    game.cpp \
    gameElements/player.cpp \
    gameElements/enemy.cpp \
    gameElements/bullet.cpp \
    gameElementsCreators/enemycreator.cpp \
    health.cpp \
    score.cpp \
    gameElements/warplane.cpp \
    gameElementsCreators/nightgecreator.cpp \
    gameElementsCreators/gameelementscreator.cpp \
    gameElementsCreators/daygecreator.cpp \
    gameElements/bulletMovingStrategy/directmoving.cpp \
    gameElements/bulletMovingStrategy/reversemoving.cpp \
    gameElements/bulletMovingStrategy/movingstrategy.cpp

HEADERS += \
    game.h \
    gameElements/player.h \
    gameElements/enemy.h \
    gameElements/bullet.h \
    gameElementsCreators/enemycreator.h \
    health.h \
    score.h \
    gameElements/warplane.h \
    gameElementsCreators/gameelementscreator.h \
    gameElementsCreators/nightgecreator.h \
    gameElementsCreators/daygecreator.h \
    gameElements/collisionsoundplayable.h \
    gameElements/bulletMovingStrategy/movingstrategy.h \
    gameElements/bulletMovingStrategy/directmoving.h \
    gameElements/bulletMovingStrategy/reversemoving.h

FORMS +=

RESOURCES += \
    resources.qrc
