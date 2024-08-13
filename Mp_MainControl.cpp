#include "Mp_MainControl.h"

MainControl::MainControl() : screen(SCR_MAIN), stateTimer(300)
{

  gfx = new Gfx();
}

void MainControl::mainLoop()
{
  stateTimer.tick();
  keyboardListener();
  switch (screen)
  {
  case SCR_GAME_TANK:
  //Serial.println (screen);

    gameTank->mainLoop();
    break;

  case SCR_MAIN:
    handlerMainScreen();
    break;

  case SCR_M_MAIN:
    handlerMainMenu();
    break;

  case SCR_OFF:
    handlerScreenOff();
    break;

  case SCR_CLOCK:
    handlerClock();
    break;
  }
}

void MainControl::handlerMainMenu()
{

  if (mainMenu == nullptr)
  {

    mainMenu = new Menu();
    mainMenu->setOffTimerOn(10000);
    mainMenu->setMenuCode(MENU_MAIN);
    mainMenu->menuFromPRGMEM();
  }
  mainMenu->menuTimersTick();
  if (mainMenu->isA1stDraw())
  {
    mainMenu->activation();
    byte a = mainMenu->getCheckedOption();
    byte a1 = mainMenu->getNeighbour(a, true);
    byte a2 = mainMenu->getNeighbour(a, false);
    byte i1 = mainMenu->getOptionBild(a1);
    byte i2 = mainMenu->getOptionBild(a2);
    byte ia = mainMenu->getOptionBild(a);

    unsigned int menuImg = mainMenu->getMenuImgNum(mainMenu->getMenuCode());
    gfx->drawMeinMenu(menuImg, i1, ia, i2);
  }

  if (btn_lt.btnState() || btn_rt.btnState())
  {

    bool revers = btn_lt.btnState();
    if (mainMenu->optionChanging(revers))
    {

      byte a = mainMenu->getCheckedOption();
      byte a1 = mainMenu->getNeighbour(a, true);
      byte a2 = mainMenu->getNeighbour(a, false);
      byte a0 = mainMenu->getNeighbour(a1, true);

      if (revers)
      {
        a0 = mainMenu->getNeighbour(a2, false);
      }
      byte ia = mainMenu->getOptionBild(a);
      byte i1 = mainMenu->getOptionBild(a1);
      byte i2 = mainMenu->getOptionBild(a2);
      byte i0 = mainMenu->getOptionBild(a0);

      byte menuImg = mainMenu->getMenuImgNum(mainMenu->getMenuCode());
      gfx->drawMeinMenu(menuImg, i1, ia, i2, i0, true, revers);
    }
  }

  if (btn_dn.btnState())
  {
    byte checkedOptionBild = mainMenu->getOptionBild(mainMenu->getCheckedOption());
    if (mainMenu->menuOpen())
    {
      gfx->menuAnimation1(checkedOptionBild);
    }
    else
    {

      if (mainMenu->getIsMenuTimerEnd() && mainMenu->getFunctionToDo(mainMenu->getCheckedOption()) != 0)
      {
        funcSelector();
      }
    }
  }
  if (btn_up.btnState())
  {
    if (mainMenu->menuClose())
    {
      gfx->menuAnimation1(mainMenu->getOptionBild(
                              mainMenu->getMenuLevelOption(mainMenu->getMenulevel())),
                          true);
    }
    else if (mainMenu->getIsMenuTimerEnd())
    {
      if (mainMenu != nullptr)
      {
        delete mainMenu;
        mainMenu = nullptr;
      }
      screenChange(SCR_MAIN);
    }
  }
}

void MainControl::handlerScreenOff()
{
  if (isDisplayOn)
  {
    gfx->displayOff();
    isDisplayOn = false;
  }
  if (btn_lt.btnState() || btn_rt.btnState() || btn_up.btnState())
  {
    screenChange(SCR_MAIN);
    isDisplayOn = true;
  }
  else if (btn_dn.btnState())
  {
    screenChange(SCR_CLOCK);
    isDisplayOn = true;
    for (unsigned int i = 0; i < 6; i++)
    {
      Serial.print(i);
      Serial.print(" = ");
      Serial.println(Menu::getMenuImgNum(i));
    }
  }
}

void MainControl::handlerClock()
{
  if (drawKey)
  {
    drawKey = false;
    gfx->drawClock();
  }

  if (btn_lt.btnState() || btn_rt.btnState() || btn_dn.btnState())
  {
    screenChange(SCR_MAIN);
    drawKey = true;
  }
  else if (btn_up.btnState())
  {
    screenChange(SCR_OFF);
    drawKey = true;
  }
}

void MainControl::handlerMainScreen()
{
  if (drawKey)
  {
    drawKey = false;
    gfx->drawMainScreen();
  }

  if (btn_up.btnState())
  {
    drawKey = true;
    screenChange(SCR_OFF);
  }
  else if (btn_dn.btnState())
  {
    drawKey = true;
    screenChange(SCR_CLOCK);
  }
  else if (btn_lt.btnState() || btn_rt.btnState())
  {
    drawKey = true;
    screenChange(SCR_M_MAIN);
  }
}

bool MainControl::screenChange(unsigned int scr)
{

  if (stateTimer.isTimerEnd())
  {
    screen = scr;
    stateTimer.timerStart();
    return true;
  }
  return false;
}

void MainControl::keyboardListener()
{
  btn_lt.buttonListener();
  btn_rt.buttonListener();
  btn_dn.buttonListener();
  btn_up.buttonListener();
  btn_st.buttonListener();
}

void MainControl::funcSelector()
{
  if (stateTimer.isTimerEnd())
  {
    stateTimer.timerStart();
    switch (mainMenu->getFunctionToDo(mainMenu->getCheckedOption()))
    {
    case FUNC_DOCTOR:
      funcDoctor();
      break;
    case FUNC_EATING:
      funcEating();
      break;
    case FUNC_GAME:
      funcGameStarter();
      break;
    case FUNC_HEALING:
      funcHealing();
      break;
    case FUNC_SHOWER:
      funcShower();
      break;
    case FUNC_SLEEP:
      funcSleep();
      break;
    case FUNC_STATUS:
      funcStatus();
      break;
    case FUNC_TOILET:
      funcToilet();
      break;

    default:
      break;
    }
  }
}

void MainControl::funcStatus()
{
}
void MainControl::funcSleep()
{
}
void MainControl::funcToilet()
{
}
void MainControl::funcShower()
{
}
void MainControl::funcEating()
{
  Serial.print("eat ");
  Serial.println(mainMenu->getCheckedOption());
}
void MainControl::funcDoctor()
{
}
void MainControl::funcHealing()
{
}
void MainControl::funcGameStarter()
{
  unsigned int gameNum = mainMenu->getCheckedOption();
  Serial.print("mem= ");
  Serial.println(freeMemory());
  if (mainMenu != nullptr)
  {
    delete mainMenu;
    mainMenu = nullptr;
  }
  if (gfx != nullptr)
  {
    delete gfx;
    gfx = nullptr;
  }

  screen = SCR_GAME_TANK;

  if (gameTank == nullptr)
  {
    gameTank = new Tank::Game();
  }

  Serial.print("mem4=");
  Serial.println(freeMemory());
}
