#include <Arduino.h>
#include "../../MP_Game.h"
#include "../../Lib_Button.h"
#include "Menu.h"
#include "Tank.h"
#include "tank_Ai.h"
#include "Gfx.h"
#include "cannonShell.h"
#include "explosion.h"
#include "Portal.h"
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>


#define MAX_TANK_COUNT 10
#define CANNON2_MAX 20
#define CANNON1_MAX 5
#define MAX_EXPLOSIONS 10
#define MAX_DEAD_ENEMYES 5

#define ENEMYS_ARMOR 1

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
        bool getExit();

        Portal *portal = nullptr;
        Tank *tank[MAX_TANK_COUNT];
        Ai *ai[MAX_TANK_COUNT];

        byte shell2TankNum[CANNON2_MAX];
        cannonShell *shell2[CANNON2_MAX];
        cannonShell *shell1[CANNON1_MAX];
        Explosion *expl[MAX_EXPLOSIONS];
        byte explosionsCount = 0;
        byte enemysCountOnScreen = 1;
        byte lives = 1;

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
        void enemyCreate(int x, int y);
        void portalCreate();
        void portalControl();
        void explosionsControl();
        void cannonControl();
        byte findFreeShell();
        byte findFreeEnemysShell();
        byte findFreeExpl();
        void gameStep();
        void killUndDelete(uint8_t tankNum);
        bool checkCorner(uint8_t corner);
       // void killTank(uint8_t tankNum);
       // void deleteTankInstance(uint8_t tankNum);
       // void deadsTanksControl(uint8_t tankNum);
       // void deadsTanksControlAfterDestroy(uint8_t tankNum);


        /// @brief Game menu creation
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
        void gameOver();
       

        // variables
        bool menudraw;
        bool gameStarted;
        byte gameScreen;
        unsigned long score = 0;
        unsigned long hiScore = 0;
        uint8_t corner = 0;

        uint8_t enemysCount = 0;
        uint8_t deadTanks[MAX_DEAD_ENEMYES];

        Timer frameTimer = Timer(35);
        Menu *menu;

        Gfx gfx = Gfx();
    };
}