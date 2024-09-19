#ifndef SHAPE_H
#define SHAPE_H

#include <Arduino.h>
#include "../../Lib_Timer.h"
namespace Tetris
{

    class Shape
    {

    public:
        virtual bool rotation(bool revers) = 0;
        virtual bool move(bool left) = 0;
        virtual int getPosXInField() = 0;
        virtual int getPosYInField() = 0;
        virtual int getPosX() = 0;
        virtual int getPosY() = 0;

        virtual void getShapeArray(uint8_t forms[6]) = 0;
        virtual void timersTick()=0;
        virtual bool step()=0; 
        virtual void setPosYInField(int pos) = 0;

    protected: 
    uint8_t posNum;
    int posX;
    int posY;
    int posXInField;
    int posYInField;
    byte weight;
    byte height;

    Timer timerMove = Timer(150);


    };

}

#endif //SHAPE_H