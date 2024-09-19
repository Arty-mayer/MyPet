#include "Shape_T.h"

Tetris::Shape_T::Shape_T()
{
    posNum = 0;
    weight = 2;
    height = 3;
    posXInField = 4;
    posYInField = 20 - height;
    posX = posXInField * 5;
    posY = posYInField * 5;
}

void Tetris::Shape_T::timersTick()
{
    timerMove.tick();
}
void Tetris::Shape_T::setPosYInField(int pos)
{
    posYInField = pos;
}
bool Tetris::Shape_T::move(bool left)
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

bool Tetris::Shape_T::rotation(bool revers)
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

bool Tetris::Shape_T::step()
{
    posYInField--;
    posY = posYInField * 5;
    return true;
}

int Tetris::Shape_T::getPosXInField()
{
    return posXInField;
}

int Tetris::Shape_T::getPosYInField()
{
    return posYInField;
}

int Tetris::Shape_T::getPosX()
{
    return posX;
}

int Tetris::Shape_T::getPosY()
{
    return posY;
}


void Tetris::Shape_T::getShapeArray(uint8_t *arr)
{
    for (byte i = 0; i < 4; i++)
    {
        arr[i] = shape[posNum][i];
    }
    arr[4] = weight;
    arr[5] = height;
}
