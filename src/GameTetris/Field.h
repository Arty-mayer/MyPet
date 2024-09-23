#ifndef TETRIS_FIELD_H
#define TETRIS_FIELD_H

#include <Arduino.h>
namespace Tetris
{

    class GameField
    {
    public:
        GameField();

        void addFigure(uint8_t *arr, int xInField, int yInField);
        bool collisionControl(uint8_t *arr, int xInField, int yInField);
        bool collisionControlSite(uint8_t *arr, int xInField, int yInField, bool left);
        int figureDown(uint8_t *arr, int xInField, int yInField); 
        
        byte checkFullLinies();
        void reductionsAnimation();
        void reduction(byte index);
        uint8_t getLvl();

        // vars
        uint16_t field[20];

    private:
        byte animetionCycle = 0;
        // variables

        uint8_t lvl;
    };
}
#endif