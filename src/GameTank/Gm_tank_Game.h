
#include <Arduino.h>
#include "../../MP_Game.h"
#include "../../Lib_Button.h"
#include "Gm_Menu.h"
#include "Gm_tank_Tank.h"
#include "Gm_tank_Ai.h"
#include "Gm_tank_Gfx.h"
#include "Gm_tank_cannonShell.h"
#include "Gm_tank_explosion.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MemoryFree.h>

// using Tank::Tank;
// using Tank::Adafruit_SSD1306;

#define MAX_TANK_COUNT 10
#define CANNON2_MAX 20
#define CANNON1_MAX 5
#define MAX_EXPLOSIONS 10

extern Button btn_lt;
extern Button btn_rt;
extern Button btn_dn;
extern Button btn_up;
extern Button btn_st;
extern Button btn_esc;
extern Button btn_md;

namespace Tank
{

    class GameTank : public Game
    {

    public:
        GameTank(); // constructor
        ~GameTank();

        void mainLoop();
        Tank *tank[MAX_TANK_COUNT];
        Ai *ai[MAX_TANK_COUNT];

        byte shell2TankNum[CANNON2_MAX];
        cannonShell *shell2[CANNON2_MAX];
        cannonShell *shell1[CANNON1_MAX];
        Explosion *expl[MAX_EXPLOSIONS];
        byte explosionsCount = 0;
        byte enemysCount = 1;
        byte lives = 1;
        bool getExit();

    private:
        bool exit = false;
        bool movmentBlockControl(byte tankNum);
        byte hittingEnemys(byte i);
        bool hittingPlayer(byte i);

        bool checkCollisionU(int x1, int y1, byte siye1, int x2, int y2, byte size2);
        bool checkCollisionD(int x1, int y1, byte siye1, int x2, int y2, byte size2);
        bool checkCollisionR(int x1, int y1, byte siye1, int x2, int y2, byte size2);
        bool checkCollisionL(int x1, int y1, byte siye1, int x2, int y2, byte size2);

        void enemysControl();
        void drawScreen();
        void tankControl();
        void explosionsControl();
        void cannonControl();
        byte findFreeShell();
        byte findFreeEnemysShell();
        byte findFreeExpl();
        void gameStep();
     //   void btnsListener();

        void menuCreate();
        void menuOptionActivation();
        bool menuOptionChange(bool revers);
        void gameInitialil();
        void menuHandler();
        void gameStart();
        void gamePause();
        void gameResume();
        void gameEnd();
        void gameExit();


        //variables
        bool menudraw;
        bool gameStarted;
        byte gameScreen;
        


        Timer frameTimer = Timer(35);
        Menu* menu;
      
        Gfx gfx = Gfx();
    };
}