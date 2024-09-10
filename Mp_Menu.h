#pragma once
#include "Lib_Timer.h"
#include "Mp_define.h"
#include "Mp_menusConst.h"
#include <MemoryFree.h>

#define MENU_MAX_LVL 5

class Menu
{

public:
    Menu(bool OffTimer);
    ~Menu();

    unsigned int getMenuCode();

    bool optionChanging(bool revers); // переключение опции

    bool isActive();         // возвращает menuOn - статус меню (активно/спит)

    bool getChangStatus(); // возращает true если была смена опции и переводит этот ключь в false
    bool activation();
    bool setCheckedOption(byte option);
    bool getIsMenuTimerEnd();
    void setLevelsCheckedOption(byte lvl, byte option);

    unsigned int getOptionBild(byte option);
    unsigned int getMenuToOpen(byte option); 
    unsigned int getFunctionToDo(byte option); 
    
    byte getMenuLevelOption(byte level); //получить номер опции меню определенного родительского уровнея
    byte getMenulevel();    // получить текущий уровень меню

    byte getCheckedOption();                // возвращает состояние changed, если оно true , то переводит его в false
    byte getNeighbour(byte num, bool left); // возвращает номер следующего/пердыдущего option относительно номера num

    void menuTimersTick(); // функция проверки таймеров меню
    void setMenuCode(unsigned int code);
    bool setActiveMenuCode(unsigned int code);
    void setOffTime(unsigned long time); // установить задержку отключенияменю
    void setOffTimerOn();
    void setOffTimerOn(unsigned int time);
    void setOffTimerOff();
    void menuOff();                       // отключает меню
    void setMenuTime(unsigned long time); // устанавливает длительность паузы до следующей возможной смены option
    void deleteOptions();
    bool menuOpen();
    bool menuClose();
    void setMenuLvl(byte lvl);
    
    byte menuLevel = 0;
    byte menuOption[MENU_MAX_LVL];
    // void createMenu();
    void menuFromPRGMEM();

    bool isA1stDraw();

    static unsigned int getMenuImgNum(unsigned int index);
    static unsigned int getHighLvlMenuNum(unsigned int index);

    // переменные
    Timer *menuOffTimer = nullptr;
    // bool customKey1 = false; // зарезервированный ключь для внешнего использования

private:
    unsigned int menuCode = 0;
    bool cycled;
    bool menuIsActive;
    byte checkedOption;
    byte optionsCount;

    Timer menuTimer = Timer(300);
    
    bool changed;
    bool OffTimerIsOn;
    bool thirstDraw;


    unsigned int **menuJS = nullptr;
    unsigned int activeMenusCode;

    
    void MenuCopying(const unsigned int (*menu)[4], byte numRows);
    bool deleteMenuJs();
};
