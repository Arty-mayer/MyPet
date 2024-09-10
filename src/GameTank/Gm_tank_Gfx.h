#ifndef GFX_H
#define GFX_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Gm_tank_imgs.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

namespace Tank
{

    class Gfx
    {
    public:
        Gfx();

        void drawScr();
        void drawCannon(int PosX, int PosY);
        void drawTank(int posX, int posY, byte movment, byte chainAnimation, byte sizeX, byte imgset);
        void drawExplosion(int x, int y, byte imgNum);
        void drawMenu (byte selected, byte lives, byte enemys);
        void drawPauseMenu(byte selected);
        void drawBorder();
    private:
        const uint8_t *getImg(byte bildSet, byte move, byte animateionNum);
        const uint8_t *getExplsImg(byte bildNum);
        const uint8_t *getMenusImg(byte bildNum);

    };
}
#endif
