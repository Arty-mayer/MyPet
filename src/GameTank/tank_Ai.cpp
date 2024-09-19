#include "tank_Ai.h"

namespace Tank
{
int Ai::enemysX = 0;
int Ai::enemysY = 0;
int Ai::enemysSize = 0;

Ai::Ai(Tank *tnk) : tank(tnk)
{
}

byte Ai::getMove(bool block)
{
    return move;
}

byte Ai::getShoot()
{
    if (shoot > 0)
    {
        shoot = 0;
        return 1;
    }
    return 0;
}

void Ai::setEmenyPos(int x, int y, int size)
{
    Ai::enemysX = x;
    Ai::enemysY = y;
    Ai::enemysSize = size;
}

void Ai::steper()
{
    if (tank->borderLock)
    {
        switch (tank->getMovement())
        {
        case UP:
            move = DOWN;
            break;
        case DOWN:
            move = UP;
            break;
        case LEFT:
            move = RIGHT;
            break;
        case RIGHT:
            move = LEFT;
            break;
        }
        tank->borderLock = false;
    }
    timerStep.tick();

    if (timerStep.isTimerEnd())
    {
        timerStep.timerStart();
        step();
    }
}

bool Ai::step()
{
   
    shoot = random (0,2);
     
    move = random (1,5);
    return true;
}
}