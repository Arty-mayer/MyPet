#include "Field.h"

Tetris::GameField::GameField()
{
    lvl = 0;
    for (byte i = 0; i < 20; i++)
    {
        field[i] = 0;
    }
}

void Tetris::GameField::addFigure(uint8_t *arr, int xInField, int yInField)
{
    for (byte i = 0; i < arr[5]; i++)
    {
        for (int pos = 0; pos < arr[4]; pos++)
        {
            if (arr[i] & (1 << pos))
            {
                byte dy = i + yInField;
                field[dy] |= (1 << (xInField + pos));
                lvl = (dy > lvl) ? dy : lvl;
            }
        }
    }
}

bool Tetris::GameField::collisionControl(uint8_t *arr, int xInField, int yInField)
{
    for (byte i = 0; i < arr[5]; i++)
    {
        for (int pos = 0; pos < arr[4]; pos++)
        {
            if (arr[i] & (1 << pos))
            {
                byte dy = i + yInField;
                if (field[dy - 1] & (1 << (pos + xInField)))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Tetris::GameField::collisionControlSite(uint8_t *arr, int xInField, int yInField, bool left)
{
    for (byte i = 0; i < arr[5]; i++)
    {
        for (int pos = 0; pos < arr[4]; pos++)
        {
            if (arr[i] & (1 << pos))
            {
                int dx = (left) ? pos + xInField - 1 : pos + xInField + 1;
                if (dx < 0 || dx > 9)
                {
                    return true;
                }
                byte dy = i + yInField;
                if (field[dy] & (1 << dx))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int Tetris::GameField::figureDown(uint8_t *arr, int xInField, int yInField)
{
    //bool a[6];
    int contactLvl = 0;
    for (uint8_t i = 0; i < arr[5]; i++)
    {
        for (byte pos = 0; pos < arr[4]; pos++)
        {
           // if (a[pos])
           // {
          //      continue;
          //  }
            if (arr[i] & (1 << pos))
            {
               // a[pos] = true;
                for (int fi = lvl; fi > -1; fi--)
                {
                    if (fi < 0 || field[fi] & (1 << (xInField + pos)))
                    {
                        contactLvl = (fi + 1 - i < contactLvl) ? contactLvl : fi + 1 - i;
                        break;
                    }
                }
            }
        }
    }
    return contactLvl;
}

byte Tetris::GameField::checkFullLinies()
{
    byte count = 0;
    for (byte i = 0; i < lvl; i++)
    {
        if (field[i] == 1023)
        {
            Serial.print("fullstr ");
            Serial.println(i);
            field[i] = 5119;
            count++;
        }
    }
    return count;
}

void Tetris::GameField::reductionsAnimation()
{
    if (animetionCycle < 2)
    {
        animetionCycle++;
        return;
    }
    else
    {
        animetionCycle = 0;
    }
    for (byte i = 0; i < lvl; i++)
    {
        if (field[i] == 21503)
        {
            reduction(i);
        }

        if (field[i] == 17407)
        {
            field[i] = 21503;
        }

        if (field[i] == 13311)
        {
            field[i] = 17407;
        }

        if (field[i] == 9215)
        {
            field[i] = 13311;
        }

        if (field[i] == 5119)
        {
            field[i] = 9215;
        }
    }
}

void Tetris::GameField::reduction(byte index)
{
    for (byte i = index; i < 19; i++)
    {
        field[i] = field[i + 1];
    }
    lvl--;
    field[19] = 0;
}

uint8_t Tetris::GameField::getLvl()
{
    return lvl;
}
