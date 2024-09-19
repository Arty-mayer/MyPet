#include "explosion.h"

Explosion::Explosion(int x, int y){
   Explosion(x,y,false); 
}

Explosion::Explosion(int x, int y, bool sizeCorrector) : posX (x), posY(y) 
{
    if (sizeCorrector){
        posX = posX - 5;
        posY = posY - 5;
    }
}

void Explosion::setX(byte X)
{
    posX = X;
}
void Explosion::setY(byte Y)
{
    posY = Y;
}

int Explosion::getX()
{
    return posX;
}
int Explosion::getY()
{
    return posY;
}

byte Explosion::getImgNum()
{
    step++; 
    if (step == 5) {
        finished = true;
        return 2;
    }
    else{

    }
    return step;
}

bool Explosion::isFinished()
{
    return finished;
}
