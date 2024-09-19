#include "Shape.h"
#define POS_COUNT 2

namespace Tetris
{

    class Shape_Z : public Shape
    {
    public:
        Shape_Z();
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
        const uint8_t shape[2][4]{
            {0b00000010,
             0b00000011,
             0b00000001,
             0b00000000},
            {0b00000011,
             0b00000110,
             0b00000000,
             0b00000000},
        };
    };
}