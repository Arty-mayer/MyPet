#include "Gfx.h"

extern Adafruit_SSD1306 display;

namespace Tetris
{
    Gfx::Gfx() {}

    void Gfx::drawScr()
    {

        display.display();
        display.clearDisplay();
    }

    void Gfx::drawMenu(byte selected, byte speed)
    {
        for (byte i = 0; i < 3; i++)
        {
            display.drawBitmap(i * 24 + 16, 10, getMenusImg(i), 18, 18, 1);
        }
        byte xCor = (selected - 1) * 24 + 9 + 16;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
        display.setCursor(45, 30);
        display.print(speed);
    }
    void Gfx::drawPauseMenu(byte selected)
    {

        display.drawBitmap(40, 10, getMenusImg(10), 18, 18, 1);
        display.drawBitmap(64, 10, getMenusImg(2), 18, 18, 1);
        byte xCor = (selected - 1) * 24 + 9 + 40;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
    }

    void Gfx::drawBorder()
    {
        display.drawRect(0, 0, 102, 52, 1);
    }

    void Gfx::drawFigure(uint8_t *arr, int x, int y)
    {
        for (byte i = 0; i < arr[5]; i++)
        {
            for (byte pos = 0; pos < arr[4]; pos++)
            {
                if (arr[i] & (1 << pos))
                {
                    display.drawBitmap(y + 5 * i + 1, x + 5 * pos + 1, partFigure, 5, 5, 1);
                }
            }
        }
    }

    void Gfx::drawField(GameField *field)
    {
        for (byte i = 0; i <= field->getLvl(); i++)
        {
            for (byte pos = 0; pos < 10; pos++)
            {
                if (field->field[i] & (1 << pos))
                {
                    display.drawBitmap(5 * i + 1, 5 * pos + 1, getFieldPartsImg(field->field[i]), 5, 5, 1);
                }
            }
        }
    }

    void Gfx::drawScore(unsigned long score)
    {
        display.setCursor(5,54);
        display.println(score);
    }

    void Gfx::drawNextFig(byte figNum)
    {
        display.drawBitmap(103, 54, getMenusNextFigImg(figNum),16,16,1);
    }

    const uint8_t *Gfx::getMenusImg(byte bildNum)
    {
        switch (bildNum)
        {
        case 0:
            return manuStart;
            break;
        case 1:
            return menuSpeed;
            break;
        case 2:
            return menuOut;
            break;
        case 10:
            return menuBack;
            break;
        }
        return nullptr;
    }
    const uint8_t *Gfx::getMenusNextFigImg(byte bildNum)
    {
        switch (bildNum)
        {
        case 1:
            return bild_I;
            break;
        case 2:
            return bild_O;
            break;
        case 3:
            return bild_S;
            break;
        case 4:
            return bild_Z;
            break;
        case 5:
            return bild_T;
            break;
        case 6:
            return bild_L;
            break;
        case 7:
            return bild_J;
            break;
        }
        return nullptr;
    }
    const uint8_t *Gfx::getFieldPartsImg(uint16_t fieldCode)
    {
        switch (fieldCode)
        {
        case 5119:
            return partAnim1;
            break;
        case 9215:
            return partAnim2;
            break;
        case 13311:
            return partAnim3;
            break;
        case 17407:
            return partAnim4;
            break;
        case 21503:
            return partAnim5;
            break;

        default:
            return partField;
            break;
        }
        return 0;
    }
}
