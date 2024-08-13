#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <Arduino.h>

class 
Explosion {
    public:

    Explosion(int x, int y);
    Explosion(int x, int y, bool sizeCorrector);

    void setX(byte X);
    void setY(byte Y);
    int getX();
    int getY();
    byte getImgNum ();
    
    bool isFinished();

    private:

    byte step = 0;
    bool finished = false;
    int posX;
    int posY;
};

#endif