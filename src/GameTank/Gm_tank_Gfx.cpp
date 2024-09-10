#include "Gm_tank_Gfx.h"

extern Adafruit_SSD1306 display;

namespace Tank
{
    Gfx::Gfx() {}

    void Gfx::drawScr()
    {

        display.display();
        display.clearDisplay();
    }

    void Gfx::drawCannon(int PosX, int PosY)
    {
        display.drawBitmap(PosX, PosY, shell1, 2, 2, 1);
    }

    void Gfx::drawTank(int posX, int posY, byte movment, byte chainAnimation, byte sizeX, byte imgset)
    {
        display.drawBitmap(posX, posY, getImg(imgset, movment, chainAnimation), sizeX, sizeX, 1);
    }

    void Gfx::drawExplosion(int x, int y, byte imgNum)
    {
        display.drawBitmap(x, y, getExplsImg(imgNum), 11, 11, 1);
    }

    void Gfx::drawMenu(byte selected, byte lives, byte enemys)
    {
        for (byte i = 0; i < 4; i++)
        {
            display.drawBitmap(i * 24 + 16, 10, getMenusImg(i), 18, 18, 1);
        }
        byte xCor = (selected - 1) * 24 + 9 + 16;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
        display.setCursor(45, 30);
        display.print(lives);
        display.setCursor(68, 30);
        display.print(enemys);
    }
    void Gfx::drawPauseMenu(byte selected)
    {

        display.drawBitmap(40, 10, getMenusImg(10), 18, 18, 1);
        display.drawBitmap(64, 10, getMenusImg(3), 18, 18, 1);
        byte xCor = (selected - 1) * 24 + 9 + 40;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
    }

    void Gfx::drawBorder()
    {
        display.drawRect(0, 0, 128, 64, 1);
    }

    const uint8_t *Gfx::getImg(byte bildSet, byte move, byte animateionNum)
    {
        switch (bildSet)
        {
        case 1:
            switch (move)
            {
            case UP:
                if (animateionNum == 1)
                {
                    return tank_up1;
                }
                else
                {
                    return tank_up2;
                }
                break;

            case DOWN:
                if (animateionNum == 1)
                {
                    return tank_dn1;
                }
                else
                {
                    return tank_dn2;
                }
                break;

            case LEFT:
                if (animateionNum == 1)
                {
                    return tank_l1;
                }
                else
                {
                    return tank_l2;
                }
                break;

            case RIGHT:
                if (animateionNum == 1)
                {
                    return tank_r1;
                }
                else
                {
                    return tank_r2;
                }
                break;
            }
        case 2:

            switch (move)
            {
            case UP:
                if (animateionNum == 1)
                {
                    return e_tank_u1;
                }
                else
                {
                    return e_tank_u2;
                }
                break;

            case DOWN:
                if (animateionNum == 1)
                {
                    return e_tank_d1;
                }
                else
                {
                    return e_tank_d2;
                }
                break;

            case LEFT:
                if (animateionNum == 1)
                {
                    return e_tank_l1;
                }
                else
                {
                    return e_tank_l2;
                }
                break;

            case RIGHT:
                if (animateionNum == 1)
                {
                    return e_tank_r1;
                }
                else
                {
                    return e_tank_r2;
                }
                break;
            }

            break;
        }
    }

    const uint8_t *Gfx::getExplsImg(byte bildNum)
    {
        switch (bildNum)
        {
        case 1:
            return expl1;
            break;
        case 2:
            return expl2;
            break;
        case 3:
            return expl3;
            break;
        case 4:
            return expl4;
            break;
        case 5:
            return expl2;
            break;
        }
        return nullptr;
    }
    const uint8_t *Gfx::getMenusImg(byte bildNum)
    {
        switch (bildNum)
        {
        case 0:
            return manuStart;
            break;
        case 1:
            return menuHeart;
            break;
        case 2:
            return e_tank_u1;
            break;
        case 3:
            return menuOut;
            break;
        case 10:
            return menuBack;
            break;
        }
        return nullptr;
    }
}
