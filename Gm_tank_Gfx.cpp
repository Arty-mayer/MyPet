#include "Gm_tank_Gfx.h"

extern Adafruit_SSD1306 display; 

namespace Tank {
Gfx::Gfx () {}

void  Gfx::drawScr(){
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
    display.drawBitmap(x,y,getExplsImg(imgNum),11,11,1);
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
}
