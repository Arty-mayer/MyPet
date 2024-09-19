#include "Shape.h"
#define POS_COUNT 2

namespace Tetris
{

    class Shape_I : public Shape
    {
    public:
        Shape_I();
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
        const uint8_t shape[POS_COUNT][4]
        {
            {0b00000001,
             0b00000001,
             0b00000001,
             0b00000001},
            {0b00001111,
             0b00000000,
             0b00000000,
             0b00000000}
        };
    };
}