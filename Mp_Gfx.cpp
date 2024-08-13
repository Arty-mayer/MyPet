#include "Arduino.h"

#include "Mp_Gfx.h"

Gfx::Gfx()  {}
// Gfx::Gfx(){}

void Gfx::drawMeinMenu(unsigned int main, unsigned int i1, unsigned int i2, unsigned int i3)
{
  drawMeinMenu(main, i1, i2, i3, 0, false, false);
}

void Gfx::drawMeinMenu(unsigned int main, unsigned int i1, unsigned int i2, unsigned int i3,
                       unsigned int i0, bool animation, bool revers)
{
  display.clearDisplay();
  if (animation)
  {
    byte x = 0;
    for (byte i = 0; i < 5; i++)
    {
      if (revers)
      {
        x = 8 + i * 8;
        display.drawBitmap(x + 80, 31, getMenuImg(i0), 32, 32, 1);
      }
      else
      {
        x = 88 - 8 - i * 8;
        display.drawBitmap(x - 80, 31, getMenuImg(i0), 32, 32, 1);
      }
      display.drawBitmap(0, 0, getMenuImg(main), 32, 32, WHITE);
      display.fillTriangle(57, 21, 69, 21, 63, 27, WHITE);
      display.drawBitmap(x - 40, 31, getMenuImg(i1), 32, 32, WHITE);
      display.drawBitmap(x, 31, getMenuImg(i2), 32, 32, WHITE);
      display.drawBitmap(x + 40, 31, getMenuImg(i3), 32, 32, WHITE);
      display.display();
      display.clearDisplay();
    }
  }
  display.drawBitmap(0, 0, getMenuImg(main), 32, 32, WHITE);
  display.fillTriangle(57, 21, 69, 21, 63, 27, WHITE);
  display.drawBitmap(8, 31, getMenuImg(i1), 32, 32, WHITE);
  display.drawBitmap(48, 31, getMenuImg(i2), 32, 32, WHITE);
  display.drawBitmap(88, 31, getMenuImg(i3), 32, 32, WHITE);
  display.display();
}

void Gfx::drawClock()
{
  display.clearDisplay();
  display.drawBitmap(0, 0, getImg(251), 128, 64, WHITE);
  display.display();
}

void Gfx::drawMainScreen()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(5, 2);
  display.println(F("My Pet's"));
  display.println(F("main screen"));
  display.display();
}

void Gfx::menuAnimation1(unsigned int menuOption)
{
  menuAnimation1(menuOption, false);
}

void Gfx::menuAnimation1(unsigned int menuOption, bool levetDown)
{
  display.clearDisplay();
  if (levetDown)
  {
    display.drawBitmap(0, 0, getMenuImg(menuOption), 32, 32, 1);
  }
  else
  {
    display.drawBitmap(48, 31, getMenuImg(menuOption), 32, 32, 1);
  }

  display.display();
  display.clearDisplay();
  int a = -1;
  byte x;
  byte y;
  for (byte i = 10; i > 0; i--)
  {
    if (levetDown)
    {
      y = 3 * (11 - i);
    }
    else
    {
      y = 3 * i;
    }
    x = y * y * 48 / 961;
    display.drawBitmap(x, y, getMenuImg(menuOption), 32, 32, 1);
    display.display();
    display.clearDisplay();
  }
  if (levetDown)
  {
    display.drawBitmap(48, 31, getMenuImg(menuOption), 32, 32, 1);
  }
  else
  {
    display.drawBitmap(0, 0, getMenuImg(menuOption), 32, 32, 1);
  }

  display.display();
}

void Gfx::displayOff()
{
  display.clearDisplay();
  display.display();
}

const uint8_t *Gfx::getImg(unsigned int imgNummer)
{
  switch (imgNummer)
  {

  case 251:
    return MyPet128x64;
    break;
    // main menu 1- ...
  }

  return 0;
}
/*
const uint8_t *Gfx::getMenuOptionsImg(unsigned int menuCode, unsigned int imgNummer)
{
  switch (menuCode)
  {
  case MENU_MAIN:
    return imgsMenuMain(imgNummer);
    break;
  case MENU_FOOD:
  return imgsMenuFood(imgNummer);

    break;
  }
  return 0;
}*/

const uint8_t *Gfx::getMenuImg(unsigned int imgNummer)
{
  switch (imgNummer)
  {
  case MENU_MAIN:
    return mainmenu32;
    break;
  case MMENU_BATH:
    return bad32;
    break;
  case MMENU_BEDROOM:
    return bed32;
    break;
  case MMENU_BOOK:
    return book32;
    break;
  case MMENU_FOOD:
    return foodm32;
    break;
  case MMENU_GAMES:
    return gamepad32;
    break;
  case MMENU_HOSPITAL:
    return hospital32;
    break;
  case MMENU_STATUS:
    return heart32;
    break;
  case FOOD_CAKE:
    return cake32;
    break;
  case FOOD_WATTER:
    return watter32;
    break;
  case BATH_SHOWER:
    return shower32;
    break;
  case BATH_TOILET:
    return toilet32;
    break;
  case GAMES_TANK:
    return tank32;
    break;
  default:
    return noimg32;
    break;
  }
}

/*
Функция изменяет скорость скролинга, выполнять после команды на скролинг...
Wire.beginTransmission(SCREEN_ADDRESS);
  Wire.write(0x00); // Command mode

  Wire.write(0x26); // Right Horizontal Scroll
  Wire.write(0x00); // Dummy byte
  Wire.write(0x00); // Start Page
  Wire.write(0x01); // Set time interval between each scroll step
  Wire.write(0x0F); // End Page
  Wire.write(0x00); // Dummy byte
  Wire.write(0xFF); // Dummy byte

  Wire.write(0x2F); // Activate Scroll
 // xyu
  Wire.endTransmission();
  */