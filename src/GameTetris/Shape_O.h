#include "Shape.h"
#define POS_COUNT 1

namespace Tetris
{

    class Shape_O : public Shape
    {
    public:
        Shape_O();
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
        const uint8_t shape[POS_COUNT][4]{
            {0b00000011,
             0b00000011,
             0b00000000,
             0b00000000},
        };
    };
}