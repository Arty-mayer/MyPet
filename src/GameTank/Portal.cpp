#include "Portal.h"

Tank::Portal::Portal(int x, int y): x(x), y(y), step(1), end(false)
{
}

Tank::Portal::~Portal()
{

}

bool Tank::Portal::isEnded()
{
    return end;
}

void Tank::Portal::steper()
{
    if (step<=12){
        step++;

    }
    else{
        end = true;
    }
}

uint8_t Tank::Portal::getStep()
{
    return step;
}
