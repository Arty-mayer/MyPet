#ifndef TETRIS_GFX_H
#define TETRIS_GFX_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include "Field.h"
#include "imgs.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

namespace Tetris
{

    class Gfx
    {
    public:
        Gfx();

        void drawScr();
        void drawMenu (byte selected, byte speed);
        void drawPauseMenu(byte selected);
        void drawBorder();
        void drawFigure(uint8_t* arr, int x, int y);
        void drawField(GameField* field);
        void drawScore(unsigned long score);
        void drawNextFig(byte figNum);

    private:
        const uint8_t *getImg(byte bildSet, byte move, byte animateionNum);
        const uint8_t *getExplsImg(byte bildNum);
        const uint8_t *getMenusImg(byte bildNum);
        const uint8_t *getMenusNextFigImg(byte bildNum);
        const uint8_t *getFieldPartsImg(uint16_t fieldCode);
    };
}
#endif
