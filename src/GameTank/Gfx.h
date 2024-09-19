#ifndef TANK_GFX_H
#define TANK_GFX_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "tank_imgs.h"

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
        void drawMenu(byte selected, byte lives, byte enemys, unsigned long score, unsigned long hiScore);
        void drawPauseMenu(byte selected, unsigned long score, unsigned long hiScore);
        void drawBorder();
        void drawGameOver();
        void drawScore(unsigned long score, unsigned long hiScore);
        void drawPortal(int x, int y, uint8_t step);

    private:
        const uint8_t *getImg(byte bildSet, byte move, byte animateionNum);
        const uint8_t *getExplsImg(byte bildNum);
        const uint8_t *getMenusImg(byte bildNum);
        const uint8_t *getPortalImg(uint8_t step);
    };
}
#endif
