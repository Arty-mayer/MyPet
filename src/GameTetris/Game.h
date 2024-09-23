#include <Arduino.h>

#include "../../Lib_Button.h"
#include "Menu.h"
#include "Gfx.h"
#include "../../MP_Game.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Field.h"
#include <MemoryFree.h>

#include "Shape_I.h"
#include "Shape_L.h"
#include "Shape_J.h"
#include "Shape_O.h"
#include "Shape_S.h"
#include "Shape_Z.h"
#include "Shape_T.h"


#define MAX_TANK_COUNT 10
#define CANNON2_MAX 20
#define CANNON1_MAX 5
#define MAX_EXPLOSIONS 10

#define LINIES_FOR_LVL 10
#define MIN_STEP_TIME 100
#define STEP_TIME_DECR 50

extern Button btn_lt;
extern Button btn_rt;
extern Button btn_dn;
extern Button btn_up;
extern Button btn_st;
extern Button btn_esc;
extern Button btn_md;

namespace Tetris
{

    class GameTetris : public Game
    {

    public:
        GameTetris(); // constructor
        ~GameTetris();

        void mainLoop();

        byte speed = 1;
        bool getExit();

    private:
        
        void figureControl();
        void shapeCreate(byte type);

        bool checkCollisionU(int x1, int y1, byte siye1, int x2, int y2, byte size2);
        bool checkCollisionD(int x1, int y1, byte siye1, int x2, int y2, byte size2);
        bool checkCollisionR(int x1, int y1, byte siye1, int x2, int y2, byte size2);
        bool checkCollisionL(int x1, int y1, byte siye1, int x2, int y2, byte size2);

        void drawScreen();

        void gameStep();
        void gameScores(byte SCount);
        void checkLinies();
    
        //   void btnsListener();
        // game Menu
        void menuCreate();
        void menuOptionActivation();
        bool menuOptionChange(bool revers);
        void menuHandler();
        void buildNewPart();
        // game control
        void gameStart();
        void gameInitialil();
        void gamePause();
        void gameResume();
        void gameEnd();
        void gameExit();
        void gameOver();

        // variables
        bool exit = false;

        bool menudraw;
        bool gameStarted;
        byte gameScreen;
        uint8_t figureCount = 7;
        uint8_t nextFigure;
        unsigned long gameScore=0;
        unsigned int stepTime;

        bool downpressed = false ;
        unsigned long minusLiniesCount = 0;

      


        Shape* figure = nullptr;
        GameField *field = nullptr;
        Menu *menu = nullptr;
        Timer timerFrame = Timer(50);
        Timer timerGameStep = Timer (1000);
        Timer timerFigureDown = Timer (500);
        

        Gfx gfx = Gfx();
    };
}