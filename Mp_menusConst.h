#pragma once
#include "Mp_define.h"
// менюшки 0 - код меню, 1 - изображение , 2 - родительское меню
const unsigned int PROGMEM menus[8][3] = {
    {MENU_MAIN, 0, 0},
    {MENU_STATUS, MMENU_STATUS, MENU_MAIN},
    {MENU_BATH, MMENU_BATH, MENU_MAIN},
    {MENU_FOOD, MMENU_FOOD, MENU_MAIN},
    {MENU_HOSPITAL, MMENU_HOSPITAL,MENU_MAIN},
    {MENU_BOOK, MMENU_BOOK,MENU_MAIN},
    {MENU_BEDROOM, MMENU_BEDROOM,MENU_MAIN},
    {MENU_GAMES, MMENU_GAMES,MENU_MAIN}
};
// главное меню 0 - изображение, 1 - код вызываемого меню, 2 - код вызываемой фукции. 
const  unsigned int PROGMEM mMenu[7][4] = {
    {MMENU_STATUS, 0, FUNC_STATUS},
    {MMENU_BATH, MENU_BATH, 0},
    {MMENU_FOOD, MENU_FOOD, 0},
    {MMENU_HOSPITAL, MENU_HOSPITAL, 0},
    {MMENU_BOOK, MENU_BOOK, 0},
    {MMENU_BEDROOM, 0, FUNC_SLEEP},
    {MMENU_GAMES, MENU_GAMES, 0},
};
// меню туалета 0 - изображение, 1 - код вызываемого меню, 2 - код вызываемой фукции. 

const  unsigned int PROGMEM bathMenu[2][4] = {
    {BATH_TOILET, 0, FUNC_TOILET},
    {BATH_SHOWER, 0, FUNC_SHOWER}
};
// меню еды 0 - изображение, 1 - код вызываемого меню, 2 - код вызываемой фукции. 

const  unsigned int PROGMEM foodMenu[8][4] = {
    {FOOD_CAKE, 0, FUNC_EATING},
    {FOOD_WATTER, 0, FUNC_EATING},
    {FOOD_CUP, 0, FUNC_EATING},
    {FOOD_FRUITS, 0, FUNC_EATING},
    {FOOD_VEGETABLES, 0, FUNC_EATING},
    {FOOD_FASTFOOD, 0, FUNC_EATING},
    {FOOD_TEE, 0, FUNC_EATING},
    {FOOD_COLA, 0, FUNC_EATING}
};

const  unsigned int PROGMEM hospital[2][4] = {
    {HOSPITAL_DOCTOR, 0, FUNC_DOCTOR},
    {HOSPITAL_HEALING, 0, FUNC_HEALING}
};

const  unsigned int PROGMEM book[3][4] = {
    {BOOK_TALES, 0, FUNC_DOCTOR},
    {BOOK_SCOOL, 0, FUNC_HEALING},
    {BOOK_ABC, 0, FUNC_HEALING}
};

const  unsigned int PROGMEM games[1][4] = {
    {GAMES_TANK, 0, FUNC_GAME},
    
};

//const unsigned int PROGMEM 