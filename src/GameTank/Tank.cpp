
#include "Tank.h"
namespace Tank
{

    Tank::Tank(int x, int y, byte move, byte imset, byte maxCannonShells) : imgSet(imset), posX(x), posY(y), movement(move), cannonMaxCount(maxCannonShells)
    {
        maxX = 128 - size;
        maxY = 64 - size;
        chainBild = 1;
        speed = 1;
        posLocked = false;
        cannon1Count = 0;
    }

    bool Tank::moveH(bool revers, bool moveBlocked)
    {

        if (posLocked)
        {
            return false;
        }

        if (revers)
        {
            borderLock = false;
            if (movement == LEFT)
            {
                posX = (moveBlocked) ? posX : posX - speed;
                if (posX < 0)
                {
                    posX = 0;
                    borderLock = true;
                }
                chainBild = (chainBild == 1) ? 2 : 1;
            }
            else
            {
                movement = LEFT;
            }
        }
        else
        {
            if (movement == RIGHT)
            {
                posX = (moveBlocked) ? posX : posX + speed;
                if (posX > maxX)
                {
                    posX = maxX;
                    borderLock = true;
                }
                chainBild = (chainBild == 1) ? 2 : 1;
            }
            else
            {
                movement = RIGHT;
            }
        }

        posLocked = true;
    }

    bool Tank::moveV(bool revers, bool moveBlocked)
    {
        if (posLocked)
        {
            return false;
        }
        if (revers)
        {
            borderLock = false;
            if (movement == UP)
            {
                posY = (moveBlocked) ? posY : posY - speed;
                if (posY < 0)
                {
                    posY = 0;
                    borderLock = true;
                }
                chainBild = (chainBild == 1) ? 2 : 1;
            }
            else
            {
                movement = UP;
            }
        }
        else
        {
            if (movement == DOWN)
            {
                posY = (moveBlocked) ? posY : posY + speed;
                if (posY > maxY)
                {
                    posY = maxY;
                    borderLock = true;
                }
                chainBild = (chainBild == 1) ? 2 : 1;
            }
            else
            {
                movement = DOWN;
            }
        }

        posLocked = true;
    }

    int Tank::getTankXPosition()
    {
        return posX;
    }

    int Tank::getTankYPosition()
    {
        return posY;
    }

    byte Tank::getBildSet()
    {
        return imgSet;
    }

    bool Tank::setposLock(bool lock)
    {
        posLocked = lock;

        return true;
    }

    byte Tank::getMovement()
    {
        return movement;
    }

    byte Tank::getChainAnimation()
    {
        return chainBild;
    }

    byte Tank::getSize()
    {
        return size;
    }

    byte Tank::getSpeed()
    {
        return speed;
    }

    bool Tank::shoot()
    {
        if (shootTimer.isTimerEnd())
        {
            if (cannon1Count < cannonMaxCount)
            {
                shootTimer.timerStart();
                cannon1Count++;
                return true;
            }
        }
        return false;
    }

    int Tank::getCannonStartX()
    {
        int dX;
        switch (movement)
        {
        case LEFT:
            dX = 0;
            break;
        case RIGHT:
            dX = size;
            break;
        default:
            dX = 8;
            break;
        }
        return posX + dX;
    }

    int Tank::getCannonStartY()
    {
        int dY;
        switch (movement)
        {
        case UP:
            dY = 0;
            break;
        case DOWN:
            dY = size;
            break;
        default:
            dY = 8;
            break;
        }
        return posY + dY;
    }
    bool Tank::isDestroyed()
    {
        return destroyed;
    }
    void Tank::hit()
    {
        hit(1);
    }
    void Tank::hit(uint8_t damage)
    {
        armor = (armor > damage) ? armor - damage : 0;
        if (armor == 0)
        {
            destroyed = true;
        }
    }
    uint8_t Tank::getArmor()
    {
        return armor;
    }
    void Tank::setArmor(uint8_t armor)
    {
        this->armor = armor;
    }
}