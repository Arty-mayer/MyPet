#include "Shape_I.h"

Tetris::Shape_I::Shape_I()
{
    posNum = 0;
    weight = 1;
    height = 4;
    posXInField = 4;
    posYInField = 20 - height;
    posX = posXInField * 5;
    posY = posYInField * 5;
}

void Tetris::Shape_I::timersTick()
{
    timerMove.tick();
}
void Tetris::Shape_I::setPosYInField(int pos)
{
    posYInField = pos;
}
bool Tetris::Shape_I::move(bool left)
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

bool Tetris::Shape_I::rotation(bool revers)
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

    if (posNum == 0)
    {
        height = 4; 
        weight = 1;
    }
    else {
        height = 1; 
        weight = 4;
    }

    if (posXInField + weight > 10)
    {
        posXInField = 10 - weight;
        posX = 5 * posXInField;
    }
    timerMove.timerStart();
    return true;
}

bool Tetris::Shape_I::step()
{
    posYInField--;
    posY = posYInField * 5;
    return true;
}

int Tetris::Shape_I::getPosXInField()
{
    return posXInField;
}

int Tetris::Shape_I::getPosYInField()
{
    return posYInField;
}

int Tetris::Shape_I::getPosX()
{
    return posX;
}

int Tetris::Shape_I::getPosY()
{
    return posY;
}


void Tetris::Shape_I::getShapeArray(uint8_t *arr)
{
    for (byte i = 0; i < 4; i++)
    {
        arr[i] = shape[posNum][i];
    }
    arr[4] = weight;
    arr[5] = height;
}
