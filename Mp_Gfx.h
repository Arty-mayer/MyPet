#pragma once
#include "Mp_imgs.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Mp_Menu.h"

extern Adafruit_SSD1306 display; 


class Gfx {
    public:
   
    Gfx();

    
    void drawMeinMenu(unsigned int main, unsigned int i1, unsigned int i2, unsigned int i3, 
        unsigned int i0, bool revers, bool animation); //Отрисовывает меню
    void drawMeinMenu( unsigned int main, unsigned int i1, unsigned int i2, unsigned int i3); // перегрузка drawmainMenu
    void drawClock();   //отрисовка заставки(часов)
    void drawMainScreen(); // отрисовка главного вида

    void menuAnimation1 (unsigned int menuOption, bool levetDown); // анимация открытия меню 
    void menuAnimation1 (unsigned int menuOption);

    void displayOff();

    const uint8_t* getImg(unsigned int imgNummer);
    const uint8_t* getMenuImg(unsigned int imgNummer);
    

    private:
    

   // Adafruit_SSD1306 &display;
    

};