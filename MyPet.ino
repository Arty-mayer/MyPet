#include "Mp_MainControl.h"
#include "Mp_menusConst.h"
#include "Mp_Gfx.h"
#include <MemoryFree.h>
#include "Lib_Timer.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

 //Adafruit_SSD1306 display(128,64,&Wire,OLED_RESET);

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
Button btn_lt = Button(8, true);
Button btn_rt = Button(7, true);
Button btn_dn = Button(6, true);
Button btn_up = Button(5, true);
Button btn_st = Button(3, true);
Button btn_md = Button(4, true);
Button btn_esc = Button(2, true);

Adafruit_SSD1306 display(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


MainControl maincontrol;

 //Game* game;
void setup()
{

  Serial.begin(115200);
  Serial.println("start");

  displayInit();
  display.clearDisplay();
   //game = new Game();
}

bool displayInit()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC)) //,SCREEN_ADDRESS))
  {
    delay(1000);
    displayInit();
  }
  else
  {
    return true;
  }
}

void loop()
{
   //game->mainLoop();
  maincontrol.mainLoop();
}
