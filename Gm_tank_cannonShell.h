#include <Arduino.h>
#include "Lib_Timer.h"

namespace Tank {

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4



class cannonShell
{

public:
    cannonShell(byte x, byte y, byte dir);
    int getX();
    int getY();

    bool flyStep();
    void setPosLock(bool lock);

    void contact();
    bool getExplosed();

    byte getDirection();
    byte getSize();

     bool explosed = false;

private:
    
    byte direction;
    byte speed;
    bool posLocked;
    int posX;
    int posY;
    byte size = 2;
};

}