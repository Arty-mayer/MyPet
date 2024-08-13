#include <Arduino.h>
#include "Lib_Timer.h"
#include "Mp_Menu.h"
#include "Lib_Button.h"
#include "Mp_Gfx.h"
#include <MemoryFree.h>
#include "Mp_define.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Gm_tank_Game.h"

extern Button btn_lt;
extern Button btn_rt;
extern Button btn_dn;
extern Button btn_up;
extern Button btn_st;

using Tank::Game;

class MainControl
{

public:


  MainControl(); // constructor

  void mainLoop();


private:
//methodes
  void keyboardListener();

  void handlerMainMenu();
  void handlerScreenOff();
  void handlerClock();
  void handlerMainScreen();

  void funcStatus();
  void funcSleep();
  void funcToilet();
  void funcShower();
  void funcEating();
  void funcDoctor();
  void funcHealing();
  void funcGameStarter();

  void funcSelector();


 //variables
  bool drawKey = true; // для MyPet logo
  bool screenChange(unsigned int scr);

 //  Adafruit_SSD1306 display;
  Menu *mainMenu = nullptr;
  Gfx *gfx = nullptr;
  bool isDisplayOn;
  Timer stateTimer;

  Tank::Game* gameTank = nullptr;

  unsigned int screen; // экран для отображения
                       // меню, которое должно быть на экране
};
