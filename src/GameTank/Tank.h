#ifndef TANK_H
#define TANK_H


#include <Arduino.h>
#include "../../Lib_Timer.h"

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

namespace Tank
{

class Tank
{
public:
 
  Tank(int x, int y, byte move, byte imgset, byte maxCannonShells);

  bool moveH(bool revers, bool moveBlocked);
  bool moveV(bool revers, bool moveBlocked);

  bool setposLock(bool lock);
  int getTankXPosition();
  int getTankYPosition();

  byte getBildSet();
  byte getMovement();
  byte getChainAnimation();
  byte getSize();
  byte getSpeed();
  bool shoot();
  int getCannonStartX();
  int getCannonStartY();

  bool isDestroyed();


  // vars
  byte cannon1Count = 0;
  Timer shootTimer = Timer(200);
  bool borderLock = false;


  void hit();
  void hit(uint8_t damage);
  uint8_t getArmor();
  void setArmor(uint8_t arm);

private:
  // methodes

  // variables

  byte speed ;
  byte size = 18;
  uint8_t armor  = 1; 
  bool destroyed = false;

  int posX;
  int posY;

  byte maxX;
  byte maxY;

  byte chainBild ;
  bool posLocked;

  byte movement;

  byte imgSet; // для определения набора текстур
  byte cannonMaxCount ;
};
}
#endif