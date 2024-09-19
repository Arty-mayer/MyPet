#include "Shape_L.h"

Tetris::Shape_L::Shape_L()
{
    posNum = 0;
    weight = 2;
    height = 3;
    posXInField = 4;
    posYInField = 20 - height;
    posX = posXInField * 5;
    posY = posYInField * 5;
}

void Tetris::Shape_L::timersTick()
{
    timerMove.tick();
}
void Tetris::Shape_L::setPosYInField(int pos)
{
    posYInField = pos;
}
bool Tetris::Shape_L::move(bool left)
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

bool Tetris::Shape_L::rotation(bool revers)
{
    if (!timerMove.isTimerEnd())
    {
        return false;
    }

    if (revers)
    {
        if (posNum == 0)
        {
            posNum = POS_COUNT - 1;
        }
        else
        {
            posNum--;
        }
    }
    else
    {
        if (posNum == POS_COUNT - 1)
        {
            posNum = 0;
        }
        else
        {
            posNum++;
        }
    }

    if (posNum == 0 || posNum == 2)
    {
        height = 3; 
        weight = 2;
    }
    else {
        height = 2; 
        weight = 3;
    }

    if (posXInField + weight > 10)
    {
        posXInField = 10 - weight;
        posX = 5 * posXInField;
    }
    timerMove.timerStart();
    return true;
}

bool Tetris::Shape_L::step()
{
    posYInField--;
    posY = posYInField * 5;
    return true;
}

int Tetris::Shape_L::getPosXInField()
{
    return posXInField;
}

int Tetris::Shape_L::getPosYInField()
{
    return posYInField;
}

int Tetris::Shape_L::getPosX()
{
    return posX;
}

int Tetris::Shape_L::getPosY()
{
    return posY;
}


void Tetris::Shape_L::getShapeArray(uint8_t *arr)
{
    for (byte i = 0; i < 4; i++)
    {
        arr[i] = shape[posNum][i];
    }
    arr[4] = weight;
    arr[5] = height;
}
