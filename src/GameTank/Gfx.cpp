#include "Gfx.h"

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

    void Gfx::drawMenu(byte selected, byte lives, byte enemys, unsigned long score, unsigned long hiScore)
    {
        for (byte i = 0; i < 4; i++)
        {
            display.drawBitmap(i * 24 + 16, 10, getMenusImg(i), 18, 18, 1);
        }
        byte xCor = (selected - 1) * 24 + 9 + 16;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
        display.setTextSize(1);
        display.setCursor(47, 30);
        display.print(lives);
        display.setCursor(70, 30);
        display.print(enemys);
        display.setCursor(0, 45);
        //display.setTextSize(1);
        display.print("Score: ");
        display.print(score);
        display.setCursor(0, 55);
        display.print("Hi score: ");
        display.print(hiScore);
    }
    void Gfx::drawPauseMenu(byte selected, unsigned long score, unsigned long hiScore)
    {

        display.drawBitmap(40, 10, getMenusImg(10), 18, 18, 1);
        display.drawBitmap(64, 10, getMenusImg(3), 18, 18, 1);
        byte xCor = (selected - 1) * 24 + 9 + 40;
        display.fillTriangle(xCor - 6, 01, xCor + 6, 01, xCor, 07, WHITE);
        display.setCursor(0, 45);
        display.setTextSize(1);
        display.print("Score: ");
        display.print(score);
        display.setCursor(0, 55);
        display.print("Hi score: ");
        display.print(hiScore);
    }

    void Gfx::drawBorder()
    {
        display.drawRect(0, 0, 128, 64, 1);
    }

    void Gfx::drawGameOver()
    {
        display.setTextSize(3);
        display.setCursor(30, 10);
        display.print("Game");
         display.setCursor(30, 30);
        display.print("Over");
        // display.display();
        // display.clearDisplay();
    }

    void Gfx::drawScore(unsigned long score, unsigned long hiScore)
    {
        display.setTextSize(1);
        display.setCursor(20, 10);
        display.print("Score: ");
        display.setCursor(20, 20);
        display.print(score);
        display.setCursor(20, 40);
        display.print("Hi score: ");
        display.setCursor(20, 50);
        display.print(hiScore);
        // display.display();
        // display.clearDisplay();
    }

    void Gfx::drawPortal(int x, int y, uint8_t step)
    {
        display.drawBitmap(x,y,getPortalImg(step),18,18,1);
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
    const uint8_t *Gfx::getPortalImg(uint8_t step)
    {
        switch (step)
        {
        case 1:
            return portal1;
            break;
            case 2:
            return portal2;
            break;
            case 3:
            return portal3;
            break;
            case 4:
            return portal4;
            break;
            case 5:
            return portal5;
            break;
            case 6:
            return portal6;
            break;
            case 7:
            return portal7;
            break;
            case 8:
            return portal8;
            break;
            case 9:
            return portal9;
            break;
            case 10:
            return portal10;
            break;
            case 11:
            return portal11;
            break;
            case 12:
            return portal12;
            break;
        }
        return nullptr;
    }
}
