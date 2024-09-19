#ifndef AI_H
#define AI_H

#include "../../Lib_Timer.h"
#include "Tank.h"

namespace Tank
{

    class Ai
    {

    public:
        Ai(Tank *tnk);

        byte getMove(bool block);
        byte getShoot();
        void static setEmenyPos(int x, int y, int size);
        void steper();

        bool step();

        static int enemysX;
        static int enemysY;
        static int enemysSize;

    private:
        bool movementBlocked;
        byte move;
        byte shoot;
        Timer timerStep = Timer(300);
        Tank *tank;
    };
} // namespace Tank

#endif