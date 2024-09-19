#include "Game.h"

namespace Tetris
{

    GameTetris::GameTetris()
    {
        gameInitialil();
        gameStarted = false;
        gameScreen = 0;
        gfx.drawScr();
        delay(300);
    }

    GameTetris::~GameTetris()
    {
        gameEnd();
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        delay(300);
    }

    void GameTetris::gameInitialil()
    {
        figure = nullptr;
        menu = nullptr;
    }

    void GameTetris::menuHandler()
    {
        menudraw = false;
        if (menu == nullptr)
        {
            menuCreate();
            if (gameStarted)
            {

                gfx.drawPauseMenu(menu->getCheckedOption());
                gfx.drawScr();
            }
            else
            {
                gfx.drawMenu(menu->getCheckedOption(), speed);
                gfx.drawScr();
            }
        }
        menu->menuTimersTick();

        if (btn_rt.btnState() || btn_lt.btnState())
        {
            menudraw = menu->optionChanging(btn_lt.btnState());
        }
        if (btn_up.btnState() || btn_dn.btnState())
        {
            menudraw = menuOptionChange(btn_dn.btnState());
        }
        if (btn_st.btnState())
        {
            menuOptionActivation();
        }
        if (menudraw)
        {
            if (gameStarted)
            {

                gfx.drawPauseMenu(menu->getCheckedOption());
                gfx.drawScr();
            }
            else
            {
                gfx.drawMenu(menu->getCheckedOption(), speed);
                gfx.drawScr();
            }
        }
    }

    void GameTetris::buildNewPart()
    {
        uint8_t arr[6];
        figure->getShapeArray(arr);
        field->addFigure(arr, figure->getPosXInField(), figure->getPosYInField());
        checkLinies();
    }

    bool GameTetris::menuOptionChange(bool revers)
    {
        if (gameStarted)
        {
            return false;
        }
        if (menu->getCheckedOption() == 2)
        {
            if (menu->getTimerIsEnd())
            {
                menu->timerRestart();
                speed = (revers) ? speed - 1 : speed + 1;
                if (speed < 1)
                {
                    speed = 1;
                }
                if (speed > 15)
                {
                    speed = 15;
                }
                return true;
            }
        }

        return false;
    }

    void GameTetris::menuCreate()
    {
        if (menu != nullptr)
        {
            return;
        }
        menu = new Menu;
        if (gameStarted)
        {
            menu->addOption(2);
        }
        else
        {
            menu->addOption(3);
        }
    }

    void GameTetris::menuOptionActivation()
    {
        if (gameStarted)
        {
            switch (menu->getCheckedOption())
            {
            case 1:
                gameResume();
                break;
            case 2:
                gameEnd();
                break;
            }
        }
        else
        {
            switch (menu->getCheckedOption())
            {
            case 1:
                gameStart();
                break;
            case 3:
                gameExit();
                break;
            }
        }
    }

    void GameTetris::gameStart()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }

        // to do написать стартер
        if (field != nullptr)
        {
            delete field;
            field = nullptr;
        }
        gameScore = 0;
        field = new GameField;
        shapeCreate(random(1, figureCount + 1));
        nextFigure = random(1, figureCount + 1);
        gameStarted = true;
        timerFrame.timerStart();
        timerGameStep.timerStart();
        gameScreen = 1;
        delay(200);
    }

    void GameTetris::gamePause()
    {
        timerFrame.timerStop();
        gameScreen = 0;
        delay(300);
    }

    void GameTetris::gameResume()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        delay(500);
        timerFrame.timerStart();
        gameScreen = 1;
    }

    void GameTetris::gameEnd()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        timerFrame.timerStop();
        timerGameStep.timerStop();
        gameStarted = false;
        gameScreen = 0;

        delay(300);
    }

    void GameTetris::gameExit()
    {
        exit = true;
        gameEnd();
    }

    void GameTetris::gameOver()
    {
        gameStarted = false;
        timerGameStep.timerStop();
        // timerFrame.timerStop();
    }

    void GameTetris::mainLoop()
    {
        if (exit)
        {
            return;
        }
        if (gameScreen == 0)
        {
            menuHandler();
            return;
        }
        timerGameStep.tick();
        if (timerGameStep.isTimerEnd())
        {
            timerGameStep.timerStart();
            gameStep();
        }
        timerFigureDown.tick();
        if (figure != nullptr)
        {
            figureControl();
            figure->timersTick();
        }
        timerFrame.tick();

        if (timerFrame.isTimerEnd())
        {
            timerFrame.timerStart();

            drawScreen();
            field->reductionsAnimation();

            if (btn_esc.btnState())
            {
                gamePause();
            }
        }
    }

    void GameTetris::drawScreen()
    {
        gfx.drawBorder();
        uint8_t arr[6];
        for (byte i = 0; i < 4; i++)
        {
            arr[i] = 0;
        }
        if (field != nullptr)
        {
            gfx.drawField(field);
        }
        if (figure != nullptr)
        {
            figure->getShapeArray(arr);
            gfx.drawFigure(arr, figure->getPosX(), figure->getPosY());
        }
        gfx.drawNextFig(nextFigure);
        gfx.drawScore(gameScore);
        gfx.drawScr();
    }

    void GameTetris::figureControl()
    {
        if (figure == nullptr)
        {
            return;
        }
        uint8_t arr[6];
        figure->getShapeArray(arr);
        if (btn_lt.btnState() || btn_rt.btnState())
        {

            if (!field->collisionControlSite(arr, figure->getPosXInField(), figure->getPosYInField(), btn_lt.btnState()))
            {
                figure->move(btn_lt.btnState());
            }
        }

        if (btn_up.btnState())
        {
            figure->rotation(btn_up.btnState());
        }
        if (btn_dn.btnState() && !downpressed)
        {
            timerGameStep.setTime(40);
            downpressed = true;
        }
        if (downpressed && !btn_dn.btnState())
        {
            timerGameStep.setTime(stepTime);
            downpressed = false;
        }
        if (btn_st.btnState())
        {
            if (timerFigureDown.isTimerEnd())
            {
                figure->setPosYInField(field->figureDown(arr, figure->getPosXInField(), figure->getPosYInField()));
                timerFigureDown.timerStart();
            }
        }
    }

    void GameTetris::shapeCreate(byte type)
    {
        if (figure != nullptr)
        {
            delete figure;
            figure = nullptr;
        }
        switch (type)
        {
        case 1:
            figure = new Shape_I();
            break;
        case 2:
            figure = new Shape_O();
            break;
        case 3:
            figure = new Shape_S();
            break;
        case 4:
            figure = new Shape_Z();
            break;
        case 5:
            figure = new Shape_T();
            break;
        case 6:
            figure = new Shape_L();
            break;
        case 7:
            figure = new Shape_J();
            break;
        }
    }

    bool GameTetris::getExit()
    {
        return exit;
    }

    bool GameTetris::checkCollisionU(int x1, int y1, byte size1, int x2, int y2, byte size2)
    {
        if (y1 <= y2 + size2 && y1 >= y2)
        {
            if (x1 + size1 > x2 && x1 < x2 + size2)
            {
                return true;
            }
        }
        return false;
    }
    bool GameTetris::checkCollisionD(int x1, int y1, byte size1, int x2, int y2, byte size2)
    {
        if (y1 + size1 >= y2 && y1 + size1 <= y2 + size2)
        {
            if (x1 + size1 > x2 && x1 < x2 + size2)
            {
                return true;
            }
        }
        return false;
    }
    bool GameTetris::checkCollisionL(int x1, int y1, byte size1, int x2, int y2, byte size2)
    {
        if (x1 <= x2 + size2 && x1 >= x2)
        {
            if (y1 + size1 > y2 && y1 < y2 + size2)
            {
                return true;
            }
        }
        return false;
    }
    bool GameTetris::checkCollisionR(int x1, int y1, byte size1, int x2, int y2, byte size2)
    {
        if (x1 + size1 >= x2 && x1 + size1 <= x2 + size2)
        {
            if (y1 + size1 > y2 && y1 < y2 + size2)
            {
                return true;
            }
        }
        return false;
    }

    void GameTetris::gameStep()
    {
        if (field->getLvl() >= 19)
        {
            Serial.println("game over");
            gameOver();
        }
        checkLinies();
        if (figure != nullptr)
        {
            uint8_t arr[6];
            figure->getShapeArray(arr);
            if (field->collisionControl(arr, figure->getPosXInField(), figure->getPosYInField()) || figure->getPosYInField() == 0)
            {
                buildNewPart();

                delete figure;
                figure = nullptr;
                shapeCreate(nextFigure);
                nextFigure = random(1, figureCount + 1);

                return;
            }
            figure->step();
        }
    }

    void GameTetris::gameScores(byte SCount)
    {
        gameScore = gameScore + SCount * SCount;
    }
    void GameTetris::checkLinies()
    {
        byte a = field->checkFullLinies();
        if (a > 0)
        {
            minusLiniesCount = minusLiniesCount + a;
            gameScores(a);
            if (minusLiniesCount >= LINIES_FOR_LVL)
            {
                minusLiniesCount = 0;
                if (stepTime > MIN_STEP_TIME)
                {
                    stepTime = stepTime - STEP_TIME_DECR;
                    stepTime = (stepTime < MIN_STEP_TIME) ? MIN_STEP_TIME : stepTime;
                    timerGameStep.setTime(stepTime);
                }
            }
        }
    }
}