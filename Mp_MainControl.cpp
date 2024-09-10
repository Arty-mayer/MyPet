#include "Mp_MainControl.h"

MainControl::MainControl() : screen(SCR_MAIN), stateTimer(300), SleepTimer(15000)
{

  gfx = new Gfx();
}

void MainControl::mainLoop()
{
  SleepTimer.tick();
  stateTimer.tick();
  keyboardListener();
  switch (screen)
  {
  case SCR_GAME:

    if (game != nullptr)
    {
      game->mainLoop();
    }
    if (game->getExit())
    {
      gameExit();
    }

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

    mainMenu = new Menu(true);
    mainMenu->setOffTimerOn(6000);
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
  if (!mainMenu->isActive())
  {
    screen = SCR_MAIN;
    SleepTimer.timerStart();
    delete mainMenu;
    mainMenu = nullptr;
    return;
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

      
      Serial.print(a1);Serial.print(" / ");
      Serial.print(a);Serial.print(" / ");
      Serial.print(a2);Serial.print(" / ");
      Serial.println(a0);

      byte menuImg = mainMenu->getMenuImgNum(mainMenu->getMenuCode());
      gfx->drawMeinMenu(menuImg, i1, ia, i2, i0, true, revers);
    }
  }

  if (btn_st.btnState())
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
        if (mainMenu->menuOffTimer != nullptr)
        {
          mainMenu->menuOffTimer->timerStart();
        }

        funcSelector();
      }
    }
  }
  if (btn_esc.btnState())
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
      SleepTimer.timerStart();
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
  if (btn_lt.btnState() || btn_rt.btnState() || btn_esc.btnState())
  {
    screenChange(SCR_MAIN);
    SleepTimer.timerStart();
    isDisplayOn = true;
  }
  else if (btn_st.btnState())
  {
    screenChange(SCR_CLOCK);
    SleepTimer.timerStart();
    isDisplayOn = true;
  }
}

void MainControl::handlerClock()
{
  if (SleepTimer.isTimerEnd())
  {
    drawKey = true;
    screen = SCR_OFF;
  }
  if (drawKey)
  {
    drawKey = false;
    gfx->drawClock();
    SleepTimer.timerStart();
  }

  if (btn_lt.btnState() || btn_rt.btnState() || btn_st.btnState())
  {
    screenChange(SCR_MAIN);
    SleepTimer.timerStart();
    drawKey = true;
  }
  else if (btn_esc.btnState())
  {
    screenChange(SCR_OFF);
    drawKey = true;
  }
}

void MainControl::handlerMainScreen()
{

  if (SleepTimer.isTimerEnd())
  {
    screen = SCR_CLOCK;
    drawKey = true;
  }
  if (drawKey)
  {
    drawKey = false;
    gfx->drawMainScreen();
    SleepTimer.timerStart();
  }

  if (btn_esc.btnState())
  {
    drawKey = true;
    screenChange(SCR_OFF);
  }
  else if (btn_st.btnState())
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
  btn_esc.buttonListener();
  btn_md.buttonListener();
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

  screen = SCR_GAME;
  switch (gameNum)
  {
  case 1:
    if (game == nullptr)
    {
      game = new Tank::GameTank();
    }
    break;

  default:
    break;
  }
}

void MainControl::gameExit()
{
  Serial.print("fm3=");
  Serial.println(freeMemory());
  if (game != nullptr)
  {
    delete game;
    game = nullptr;
  }

  Serial.print("fm4=");
  Serial.println(freeMemory());

  screen = SCR_M_MAIN;
  mainMenu = new Menu(true);
  mainMenu->setOffTimerOn(3000);
  mainMenu->setMenuLvl(1);
  mainMenu->setMenuCode(MENU_GAMES);
  mainMenu->setLevelsCheckedOption(0, MMENU_GAMES);
  mainMenu->menuFromPRGMEM();
}
