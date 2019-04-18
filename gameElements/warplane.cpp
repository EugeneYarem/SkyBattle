#include "warplane.h"
#include <QDebug>

Warplane::~Warplane()
{
    delete mPlayerShut;
    delete mPlayerDestruction;
}

void Warplane::playCollisionSound() const
{
    mPlayerDestruction->play();
}
