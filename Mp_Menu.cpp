#include "Mp_Menu.h"

Menu::Menu(bool cycl) : checkedOption(1), optionsCount(0), menuIsActive(false), OffTimerIsOn(false), cycled(cycl) {
    menuOffTimer = nullptr;
}

Menu::~Menu()
{
    if (menuJS != nullptr)
    {
        deleteMenuJs();
    }
    if (menuOffTimer != nullptr)
    {
        delete menuOffTimer;
        menuOffTimer = nullptr;
    }
}

unsigned int Menu::getMenuCode()
{
    return menuCode;
}

void Menu::setMenuCode(unsigned int code)
{
    activeMenusCode = code;
}

bool Menu::optionChanging(bool revers)
{
    if (menuTimer.isTimerEnd())
    {
        if (OffTimerIsOn)
        {
            if (menuOffTimer == nullptr)
            {
                menuOffTimer = new Timer(10000);
            }
            menuOffTimer->timerStart();
        }
        menuTimer.timerStart();
        if (optionsCount < 1)
        {
            return false;
        }
        if (!menuIsActive)
        {
            menuIsActive = true;
        }
        else
        {
            switch (revers)
            {
            case true:
                if (checkedOption <= 1)
                {
                    if (cycled)
                    {
                        checkedOption = optionsCount;
                    }
                    else
                    {
                        checkedOption = 1;
                        return false;
                    }
                }
                else
                {
                    checkedOption--;
                }
                break;
            default:
                if (checkedOption >= optionsCount)
                {
                    if (cycled)
                    {
                        checkedOption = 1;
                    }
                    else
                    {
                        checkedOption = optionsCount;
                        return false;
                    }
                }
                else
                {
                    checkedOption++;
                }
                break;
            }
        }
        changed = true;
        return true;
    }
    return false;
}

void Menu::menuTimersTick()
{
    menuTimer.tick();
    if (OffTimerIsOn)
    {
        menuOffTimer->tick();
        if (menuIsActive)
        {
            if (menuOffTimer->isTimerEnd())
            {
                menuOff();
            }
        }
    }
    if (menuCode != activeMenusCode)
    {
        menuFromPRGMEM();
    }
}

byte Menu::getCheckedOption()
{
    return checkedOption;
}

bool Menu::isActive()
{
    return menuIsActive;
}

bool Menu::getChangStatus()
{
    if (changed)
    {
        changed = false;
        return true;
    }
    else
    {
        return false;
    }
}

byte Menu::getNeighbour(byte num, bool left)
{
    if (num > optionsCount)
    {
        return 0;
    }
    byte a = 0;
    switch (left)
    {
    case true:
        a = num - 1;
        break;

    default:
        a = num + 1;
        break;
    }
    if (a < 1)
    {
        if (cycled)
        {
            a = optionsCount;
        }
        else
        {
            a = 0;
        }
    }
    else if (a > optionsCount)
    {
        if (cycled)
        {
            a = 1;
        }
        else
        {
            a = 0;
        }
    }
    return a;
}

void Menu::setOffTime(unsigned long time)
{
    menuOffTimer->setTime(time);
}


void Menu::setOffTimerOn(unsigned int time)
{
    OffTimerIsOn = true;
    menuOffTimer = new Timer(time);
}

void Menu::setOffTimerOff()
{
    OffTimerIsOn = false;
    delete menuOffTimer;
    menuOffTimer = nullptr;
}

void Menu::menuOff()
{
    menuIsActive = false;
}

void Menu::setMenuTime(unsigned long time)
{
    menuTimer.setTime(time);
}

void Menu::deleteOptions()
{
    checkedOption = 1;
    optionsCount = 0;
}

bool Menu::menuOpen()
{
    if (menuTimer.isTimerEnd() && getMenuToOpen(checkedOption) != 0)
    {
        menuTimer.timerStart();
        if (OffTimerIsOn){
            menuOffTimer->timerStart();
        }
        activeMenusCode = getMenuToOpen(checkedOption);
        menuOption[menuLevel] = checkedOption;
        menuLevel++;
        if (menuCode != activeMenusCode)
        {
            menuFromPRGMEM();
        }
        return true;
    }
    return false;
}

bool Menu::menuClose()
{
    if (menuTimer.isTimerEnd())
    {
        if (menuLevel == 0)
        {
            return false;
        }
        menuTimer.timerStart();
        if (OffTimerIsOn){
            menuOffTimer->timerStart();
        }
        activeMenusCode = getHighLvlMenuNum(activeMenusCode);
        if (activeMenusCode != menuCode)
        {
            menuFromPRGMEM();
        }
        menuLevel--;
        checkedOption = menuOption[menuLevel];
        return true;
    }
    return false;
}

void Menu::setMenuLvl(byte lvl)
{
    menuLevel = lvl;
}

bool Menu::isA1stDraw()
{
    if (thirstDraw)
    {
        thirstDraw = false;
        return true;
    }
    return false;
}

unsigned int Menu::getMenuImgNum(unsigned int index)
{
    return pgm_read_word(&menus[index][1]);
}

unsigned int Menu::getHighLvlMenuNum(unsigned int index)
{
    return pgm_read_word(&menus[index][2]);
}

bool Menu::activation()
{
    if (!menuIsActive)
    {
        menuIsActive = true;
        menuTimer.timerStart();
        if (OffTimerIsOn)
        {
            menuOffTimer->timerStart();
        }
        return true;
    }
    return false;
}

bool Menu::setCheckedOption(byte option)
{
    if (option == 0 || option > optionsCount)
    {
        return false;
    }
    checkedOption = option;
    return true;
}

bool Menu::getIsMenuTimerEnd()
{
    return menuTimer.isTimerEnd();
}

void Menu::setLevelsCheckedOption(byte lvl, byte option)
{
    if (lvl > MENU_MAX_LVL || option > 254) {
        return;
    }
    menuOption[lvl] = option;
}

bool Menu::setActiveMenuCode(unsigned int code)
{
    if (menuTimer.isTimerEnd())
    {
        activeMenusCode = code;
        menuFromPRGMEM();
        return true;
    }
    return false;
}

unsigned int Menu::getOptionBild(byte option)
{
    if (menuJS != nullptr)
    {
        return menuJS[option][0];
    }
    return 0;
}

unsigned int Menu::getMenuToOpen(byte option)
{
    if (menuJS != nullptr)
    {
        return menuJS[option][1];
    }
    return 0;
}

unsigned int Menu::getFunctionToDo(byte option)
{
    if (menuJS != nullptr)
    {
        return menuJS[option][2];
    }
    return 0;
}

byte Menu::getMenuLevelOption(byte level)
{
    if (level > menuLevel)
    {
        return 0;
    }
    return menuOption[level];
}

byte Menu::getMenulevel()
{
    return menuLevel;
}

void Menu::menuFromPRGMEM()
{
    switch (activeMenusCode)
    {
    case MENU_MAIN:
        MenuCopying(mMenu, sizeof(mMenu) / sizeof(mMenu[0]));
        break;
    case MENU_FOOD:
        MenuCopying(foodMenu, sizeof(foodMenu) / sizeof(foodMenu[0]));
        break;
    case MENU_BATH:
        MenuCopying(bathMenu, sizeof(bathMenu) / sizeof(bathMenu[0]));
        break;
    case MENU_HOSPITAL:
        MenuCopying(hospital, sizeof(hospital) / sizeof(hospital[0]));
        break;
    case MENU_BOOK:
        MenuCopying(book, sizeof(book) / sizeof(book[0]));
        break;
    case MENU_GAMES:
        MenuCopying(games, sizeof(games) / sizeof(games[0]));
        break;

    default:
        break;
    }
    menuCode = activeMenusCode;
    checkedOption = 1;
    thirstDraw = true;
}

void Menu::MenuCopying(const unsigned int (*menu)[4], byte numRows)
{

    deleteMenuJs();
    byte numCols = 3;

    menuJS = new unsigned int *[numRows + 1];
    menuJS[0] = new unsigned int[numCols];
    menuJS[0][0] = 0;
    menuJS[0][1] = 0;
    menuJS[0][2] = 0;

    for (int i = 0; i < numRows; i++)
    {
        menuJS[i + 1] = new unsigned int[numCols];
        menuJS[i + 1][0] = pgm_read_word(&menu[i][0]);
        menuJS[i + 1][1] = pgm_read_word(&menu[i][1]);
        menuJS[i + 1][2] = pgm_read_word(&menu[i][2]);
        menuJS[i + 1][3] = pgm_read_word(&menu[i][3]);
    }

    optionsCount = numRows;
}

bool Menu::deleteMenuJs()
{
    if (menuJS != nullptr)
    {
        for (int i = 0; i <= optionsCount; ++i)
        {
            delete[] menuJS[i];
        }
        delete[] menuJS;
        menuJS = nullptr;
        return true;
    }
    return false;
}
