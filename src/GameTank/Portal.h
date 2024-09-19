#ifndef PORTAL_H
#define PORTAL_H
#include <Arduino.h> 

namespace Tank{
    class Portal
    {
    private:
       //vare
       uint8_t step;
       bool end;

    public:
    
        Portal(int x, int y);
        ~Portal();
        bool isEnded();
        void steper();
        uint8_t getStep();

        //vars 
        int x;
        int y;
    };
        
}


#endif