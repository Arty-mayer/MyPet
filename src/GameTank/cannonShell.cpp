#include "cannonShell.h"

namespace Tank {
cannonShell::cannonShell(byte x, byte y, byte direction) : direction(direction), speed(2), posX(x), posY(y)
{
}

int cannonShell::getX()
{
    return posX;
}

int cannonShell::getY()
{
    return posY;
}

bool cannonShell::flyStep()
{
    if (explosed)
    {
        return false;
    }
    if (posLocked)
    {
        return false;
    }
    switch (direction)
    {
    case UP:
        posY = posY - speed;
        if (posY < 0)
        {
            posY = 0;
            explosed = true;
        }
        break;
    case DOWN:
        posY = posY + speed;
        if (posY > 62)
        {
            posY = 62;
            explosed = true;
        }
        break;
    case LEFT:
        posX = posX - speed;
        if (posX < 0)
        {
            posX = 0;
            explosed = true;
        }
        break;
    case RIGHT:
        posX = posX + speed;
        if (posX > 126)
        {
            posX = 126;
            explosed = true;
        }
        break;
    }
    posLocked = true;
}

void cannonShell::setPosLock(bool lock)
{
    posLocked = lock;
}

void cannonShell::contact()
{
    explosed = true;
}

bool cannonShell::getExplosed()
{
    return explosed;
}

byte cannonShell::getDirection()
{
    return direction;
}

byte cannonShell::getSize()
{
    return size;
}

}//namespace