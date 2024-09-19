
#ifndef MP_GAME_H
#define MP_GAME_H
#include <Arduino.h>
#include "Lib_Button.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 
#include <MemoryFree.h>



extern Button btn_lt;
extern Button btn_rt;
extern Button btn_dn;
extern Button btn_up;
extern Button btn_st;
extern Button btn_esc;



class Game
{
    
public:

    
    virtual void mainLoop()=0;
    virtual bool getExit()=0;


};

#endif