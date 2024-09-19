#include "Shape_O.h"

Tetris::Shape_O::Shape_O()
{
    posNum = 0;
    weight = 2;
    height = 2;
    posXInField = 4;
    posYInField = 20 - height;
    posX = posXInField * 5;
    posY = posYInField * 5;
}

void Tetris::Shape_O::timersTick()
{
    timerMove.tick();
}
void Tetris::Shape_O::setPosYInField(int pos)
{
    posYInField = pos;
}
bool Tetris::Shape_O::move(bool left)
{
    if (!timerMove.isTimerEnd())
    {
        return false;
    }

    if (left)
    {
        if (posXInField >0)
        {
            posXInField--;
        }
    }
    else
    {
        if (posXInField + weight < 10)
        {
            posXInField++;
        }
    }
    posX = posXInField * 5;
    timerMove.timerStart();
    return true;
}

bool Tetris::Shape_O::rotation(bool revers)
{
    
    timerMove.timerStart();
    return true;
}

bool Tetris::Shape_O::step()
{
    posYInField--;
    posY = posYInField * 5;
    return true;
}

int Tetris::Shape_O::getPosXInField()
{
    return posXInField;
}

int Tetris::Shape_O::getPosYInField()
{
    return posYInField;
}

int Tetris::Shape_O::getPosX()
{
    return posX;
}

int Tetris::Shape_O::getPosY()
{
    return posY;
}


void Tetris::Shape_O::getShapeArray(uint8_t *arr)
{
    for (byte i = 0; i < 4; i++)
    {
        arr[i] = shape[posNum][i];
    }
    arr[4] = weight;
    arr[5] = height;
}
