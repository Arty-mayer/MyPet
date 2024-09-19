#include "Shape.h"
#define POS_COUNT 4

namespace Tetris
{

    class Shape_T : public Shape
    {
    public:
        Shape_T();
        bool move(bool left);
        bool rotation(bool revers);
        bool step();
        int getPosXInField();
        int getPosYInField();
        int getPosX();
        int getPosY();
        void getShapeArray(uint8_t *arr);
        void timersTick();
        void setPosYInField(int pos);

    private:
        uint8_t position = 1;
        const uint8_t shape[POS_COUNT][4]{
            {0b00000001,
             0b00000011,
             0b00000001,
             0b00000000},
            {0b00000111,
             0b00000010,
             0b00000000,
             0b00000000},
            {0b00000010,
             0b00000011,
             0b00000010,
             0b00000000},
            {0b00000010,
             0b00000111,
             0b00000000,
             0b00000000}};
    };
}