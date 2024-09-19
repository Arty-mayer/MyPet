
#include "Game.h"

namespace Tank
{

    GameTank::GameTank()
    {
        gameInitialil();
        gameStarted = false;
        gameScreen = 0;
        gfx.drawScr();
        delay(300);
    }

    GameTank::~GameTank()
    {
        gameEnd();
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        delay(300);
    }

    void GameTank::gameInitialil()
    {
        menu = nullptr;
        for (byte i = 0; i < MAX_TANK_COUNT; i++)
        {

            tank[i] = nullptr;
            ai[i] = nullptr;
        }

        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            shell1[i] = nullptr;
        }

        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            shell2[i] = nullptr;
        }

        for (byte i = 0; i < MAX_EXPLOSIONS; i++)
        {
            expl[i] = nullptr;
        }
    }

    void GameTank::menuHandler()
    {
        menudraw = false;
        if (menu == nullptr)
        {
            menuCreate();
            if (gameStarted)
            {
                gfx.drawPauseMenu(menu->getCheckedOption(), score, hiScore);
                gfx.drawScr();
            }
            else
            {
                gfx.drawMenu(menu->getCheckedOption(), lives, enemysCountOnScreen, score, hiScore);
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
                gfx.drawPauseMenu(menu->getCheckedOption(), score, hiScore);
                gfx.drawScr();
            }
            else
            {
                gfx.drawMenu(menu->getCheckedOption(), lives, enemysCountOnScreen, score, hiScore);
                gfx.drawScr();
            }
        }
    }

    bool GameTank::menuOptionChange(bool revers)
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
                lives = (revers) ? lives - 1 : lives + 1;
                if (lives < 1)
                {
                    lives = 1;
                }
                if (lives > 5)
                {
                    lives = 5;
                }
                return true;
            }
        }
        if (menu->getCheckedOption() == 3)
        {
            if (menu->getTimerIsEnd())
            {
                menu->timerRestart();
                enemysCountOnScreen = (revers) ? enemysCountOnScreen - 1 : enemysCountOnScreen + 1;
                if (enemysCountOnScreen < 1)
                {
                    enemysCountOnScreen = 1;
                }
                if (enemysCountOnScreen > 5)
                {
                    enemysCountOnScreen = 5;
                }
                return true;
            }
        }
        return false;
    }

    void GameTank::menuCreate()
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
            menu->addOption(4);
        }
    }

    void GameTank::menuOptionActivation()
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
            case 4:
                gameExit();
                break;
            }
        }
    }

    void GameTank::gameStart()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }

        tank[0] = new Tank(0, 20, RIGHT, 1, 3);
        tank[0]->setArmor(lives);
        enemysCount = enemysCountOnScreen;

        for (byte i = 1; i <= enemysCount; i++)
        {
            uint8_t x = (i < 4) ? 50 : 90;
            uint8_t y = (i < 4) ? (i - 1) * 20 : (i - 3) * 20;
            tank[i] = new Tank(x, y, LEFT, 2, 2);
            ai[i] = new Ai(tank[i]);
            tank[i]->setArmor(ENEMYS_ARMOR);
        }

        gameScreen = 1;
        gameStarted = true;
        score = 0;
        delay(500);
        frameTimer.timerStart();

        /*
        deadTanks[0] = 0;
        deadTanks[1] = 0;
        deadTanks[2] = 0;
        deadTanks[3] = 0;
        deadTanks[4] = 0;
        */
    }

    void GameTank::gamePause()
    {
        frameTimer.timerStop();
        gameScreen = 0;
        delay(300);
    }

    void GameTank::gameResume()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        delay(500);
        frameTimer.timerStart();
        gameScreen = 1;
    }

    void GameTank::gameEnd()
    {
        if (menu != nullptr)
        {
            delete menu;
            menu = nullptr;
        }
        frameTimer.timerStop();
        gameStarted = false;
        gameScreen = 0;

        for (byte i = 0; i < MAX_TANK_COUNT; i++)
        {
            if (tank[i] != nullptr)
            {
                delete tank[i];
                tank[i] = nullptr;
            }
            if (ai[i] != nullptr)
            {
                delete ai[i];
                ai[i] = nullptr;
            }
        }

        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            if (shell1[i] != nullptr)
            {
                delete shell1[i];
                shell1[i] = nullptr;
            }
        }

        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            if (shell2[i] != nullptr)
            {
                delete shell2[i];
                shell2[i] = nullptr;
            }
        }

        for (byte i = 0; i < MAX_EXPLOSIONS; i++)
        {
            if (expl[i] != nullptr)
            {
                delete expl[i];
                expl[i] = nullptr;
            }
        }

        for (uint8_t i = 1; i < MAX_DEAD_ENEMYES; i++)
        {
            deadTanks[i] = 0;
        }
        if (portal != nullptr)
        {
            delete portal;
            portal = nullptr;
        }
        delay(200);
    }

    void GameTank::gameExit()
    {
        exit = true;
        gameEnd();
    }

    void GameTank::gameOver()
    {
        frameTimer.timerStop();
        gameStarted = false;
        if (hiScore < score)
            hiScore = score;

        gfx.drawGameOver();
        gfx.drawScr();
        delay(1500);
        gfx.drawScore(score, hiScore);
        gfx.drawScr();
        gameEnd();
        gameScreen = 2;
    }

    void GameTank::mainLoop()
    {
        if (exit)
        {
            return;
        }
        if (gameScreen == 2)
        {
            if (btn_st.btnState())
            {
                gameScreen = 0;
                delay(200);
            }
            return;
        }
        if (gameScreen == 0)
        {
            menuHandler();
            return;
        }

        frameTimer.tick();
        if (frameTimer.isTimerEnd())
        {
            frameTimer.timerStart();
            gameStep();
        }
    }

    void GameTank::drawScreen()
    {
        if (portal != nullptr)
        {
            gfx.drawPortal(portal->x, portal->y, portal->getStep());
        }

        for (byte i = 0; i < 10; i++)
        {
            if (tank[i] == nullptr)
            {
                continue;
            }
            gfx.drawTank(tank[i]->getTankXPosition(), tank[i]->getTankYPosition(), tank[i]->getMovement(), tank[i]->getChainAnimation(), tank[i]->getSize(), tank[i]->getBildSet());
        }
        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            if (shell1[i] != nullptr)
            {
                gfx.drawCannon(shell1[i]->getX(), shell1[i]->getY());
            }
        }
        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            if (shell2[i] != nullptr)
            {
                gfx.drawCannon(shell2[i]->getX(), shell2[i]->getY());
            }
        }

        for (byte i = 0; i < MAX_EXPLOSIONS; i++)
        {
            if (expl[i] != nullptr)
            {
                gfx.drawExplosion(expl[i]->getX(), expl[i]->getY(), expl[i]->getImgNum());
            }
        }
        gfx.drawBorder();
        gfx.drawScr();
    }

    byte GameTank::findFreeShell()
    {
        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            if (shell1[i] == nullptr)
            {
                return i;
            }
        }
        return 254;
    }
    byte GameTank::findFreeEnemysShell()
    {
        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            if (shell2[i] == nullptr)
            {
                return i;
            }
        }
        return 254;
    }

    void GameTank::tankControl()
    {
        if (btn_st.btnState())
        {
            if (tank[0]->shoot())
            {
                byte a = findFreeShell();
                if (a != 254)
                {
                    shell1[a] = new cannonShell(tank[0]->getCannonStartX(), tank[0]->getCannonStartY(), tank[0]->getMovement());
                }
            }
        }

        if (btn_lt.btnState() || btn_rt.btnState())
        {
            bool rev = btn_lt.btnState();
            tank[0]->moveH(rev, movmentBlockControl(0));
            Ai::setEmenyPos(tank[0]->getTankXPosition(), tank[0]->getTankYPosition(), tank[0]->getSize());
        }

        if (btn_up.btnState() || btn_dn.btnState())
        {
            bool rev = btn_up.btnState();
            tank[0]->moveV(rev, movmentBlockControl(0));
        }
        tank[0]->setposLock(false);

        enemysControl();
    }

    void GameTank::enemyCreate(int x, int y)
    {
        uint8_t a = 0;
        for (uint8_t i = 1; i < MAX_TANK_COUNT; i++)
        {
            if (tank[i] == nullptr)
            {
                a = i;
                break;
            }
        }
        uint8_t richtung = 1;
        switch (corner)
        {
        case 0:
        case 2:
            richtung = RIGHT;
            break;

        default:
            richtung = LEFT;
            break;
        }
        if (a > 0)
        {
            tank[a] = new Tank(x, y, richtung, 2, 2);
            tank[a]->setArmor(ENEMYS_ARMOR);
            ai[a] = new Ai(tank[a]);
            enemysCount++;
        }
    }

    void GameTank::portalCreate()
    {
        if (portal == nullptr)
        {
            uint8_t x = 0;
            uint8_t y = 0;
            corner = (corner == 3) ? 0 : corner + 1;
            if (!checkCorner(corner))
                corner = (corner == 3) ? 0 : corner + 1;
            switch (corner)
            {
            case 0:
                x = 0;
                y = 0;
                break;
            case 1:
                x = 109;
                y = 0;
                break;
            case 2:
                x = 0;
                y = 45;
                break;
            case 3:
                x = 109;
                y = 45;
                break;
            }
            portal = new Portal(x, y);
        }
    }

    void GameTank::portalControl()
    {
        if (portal != nullptr)
        {
            portal->steper();
            if (portal->isEnded())
            {
                enemyCreate(portal->x, portal->y);
                delete portal;
                portal = nullptr;
            }
        }
    }

    void GameTank::enemysControl()
    {
        for (byte i = 1; i < 10; i++)
        {
            if (tank[i] != nullptr && ai[i] != nullptr)
            {
                bool blocker = movmentBlockControl(i);
                switch (ai[i]->getMove(blocker))
                {
                case UP:
                    tank[i]->moveV(true, blocker);
                    break;
                case DOWN:
                    tank[i]->moveV(false, blocker);
                    break;
                case LEFT:
                    tank[i]->moveH(true, blocker);
                    break;
                case RIGHT:
                    tank[i]->moveH(false, blocker);
                    break;
                }
                tank[i]->shootTimer.tick();
                tank[i]->setposLock(false);
                if (ai[i]->getShoot() == 1)
                {
                    if (tank[i]->shoot())
                    {
                        byte a = findFreeEnemysShell();
                        if (a != 254)
                        {
                            shell2TankNum[a] = i;
                            shell2[a] = new cannonShell(tank[i]->getCannonStartX(), tank[i]->getCannonStartY(), tank[i]->getMovement());
                        }
                    }
                }
            }
        }
    }

    bool GameTank::getExit()
    {
        return exit;
    }

    bool GameTank::movmentBlockControl(byte TankNum)
    {
        for (byte i = 0; i < MAX_TANK_COUNT; i++)
        {
            if (i == TankNum || tank[i] == nullptr)
            {
                continue;
            }

            switch (tank[TankNum]->getMovement())
            {
            case UP:
                if (checkCollisionU(tank[TankNum]->getTankXPosition(), tank[TankNum]->getTankYPosition() - tank[TankNum]->getSpeed(), tank[TankNum]->getSize(), tank[i]->getTankXPosition(), tank[i]->getTankYPosition(), tank[i]->getSize()))
                {
                    return true;
                }
                break;
            case DOWN:
                if (checkCollisionD(tank[TankNum]->getTankXPosition(), tank[TankNum]->getTankYPosition() + tank[TankNum]->getSpeed(), tank[TankNum]->getSize(), tank[i]->getTankXPosition(), tank[i]->getTankYPosition(), tank[i]->getSize()))
                {
                    return true;
                }
                break;
            case LEFT:
                if (checkCollisionL(tank[TankNum]->getTankXPosition() - tank[TankNum]->getSpeed(), tank[TankNum]->getTankYPosition(), tank[TankNum]->getSize(), tank[i]->getTankXPosition(), tank[i]->getTankYPosition(), tank[i]->getSize()))
                {
                    return true;
                }
                break;
            case RIGHT:
                if (checkCollisionR(tank[TankNum]->getTankXPosition() + tank[TankNum]->getSpeed(), tank[TankNum]->getTankYPosition(), tank[TankNum]->getSize(), tank[i]->getTankXPosition(), tank[i]->getTankYPosition(), tank[i]->getSize()))
                {
                    return true;
                }
                break;
            }
        }
        return false;
    }

    byte GameTank::hittingEnemys(byte i)
    {
        for (byte b = 1; b < 10; b++)
        {
            if (tank[b] != nullptr)
            {

                switch (shell1[i]->getDirection())
                {
                case UP:
                    if (checkCollisionU(shell1[i]->getX(), shell1[i]->getY(), shell1[i]->getSize(), tank[b]->getTankXPosition(), tank[b]->getTankYPosition(), tank[b]->getSize()))
                    {
                        return b;
                    }
                    break;
                case DOWN:
                    if (checkCollisionD(shell1[i]->getX(), shell1[i]->getY(), shell1[i]->getSize(), tank[b]->getTankXPosition(), tank[b]->getTankYPosition(), tank[b]->getSize()))
                    {
                        return b;
                    }
                    break;
                case LEFT:
                    if (checkCollisionL(shell1[i]->getX(), shell1[i]->getY(), shell1[i]->getSize(), tank[b]->getTankXPosition(), tank[b]->getTankYPosition(), tank[b]->getSize()))
                    {
                        return b;
                    }
                    break;
                case RIGHT:
                    if (checkCollisionR(shell1[i]->getX(), shell1[i]->getY(), shell1[i]->getSize(), tank[b]->getTankXPosition(), tank[b]->getTankYPosition(), tank[b]->getSize()))
                    {
                        return b;
                    }
                    break;
                }
            }
        }
        return 0;
    }

    bool GameTank::hittingPlayer(byte i)
    {
        if (tank[0] != nullptr)
        {

            switch (shell2[i]->getDirection())
            {
            case UP:
                if (checkCollisionU(shell2[i]->getX(), shell2[i]->getY(), shell2[i]->getSize(), tank[0]->getTankXPosition(), tank[0]->getTankYPosition(), tank[0]->getSize()))
                {
                    return true;
                }
                break;
            case DOWN:
                if (checkCollisionD(shell2[i]->getX(), shell2[i]->getY(), shell2[i]->getSize(), tank[0]->getTankXPosition(), tank[0]->getTankYPosition(), tank[0]->getSize()))
                {
                    return true;
                }
                break;
            case LEFT:
                if (checkCollisionL(shell2[i]->getX(), shell2[i]->getY(), shell2[i]->getSize(), tank[0]->getTankXPosition(), tank[0]->getTankYPosition(), tank[0]->getSize()))
                {
                    return true;
                }
                break;
            case RIGHT:
                if (checkCollisionR(shell2[i]->getX(), shell2[i]->getY(), shell2[i]->getSize(), tank[0]->getTankXPosition(), tank[0]->getTankYPosition(), tank[0]->getSize()))
                {
                    return true;
                }
                break;
            }
        }

        return false;
    }

    bool GameTank::checkCollisionU(int x1, int y1, byte size1, int x2, int y2, byte size2)
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
    bool GameTank::checkCollisionD(int x1, int y1, byte size1, int x2, int y2, byte size2)
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
    bool GameTank::checkCollisionL(int x1, int y1, byte size1, int x2, int y2, byte size2)
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
    bool GameTank::checkCollisionR(int x1, int y1, byte size1, int x2, int y2, byte size2)
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

    void GameTank::explosionsControl()
    {

        for (byte i = 0; i < MAX_EXPLOSIONS; i++)
        {
            if (expl[i] != nullptr && expl[i]->isFinished())
            {
                delete expl[i];
                expl[i] = nullptr;
                explosionsCount--;
            }
        }
    }

    void GameTank::cannonControl()
    {
        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            if (shell1[i] != nullptr)
            {
                shell1[i]->flyStep();

                byte a = hittingEnemys(i);

                if (a != 0)
                {
                    shell1[i]->explosed = true;
                    bool tankDestr = tank[a]->isDestroyed();
                    tank[a]->hit();
                    if (tank[a]->getArmor() == 0)
                    {
                        killUndDelete(a);
                        /*
                         if (tankDestr)
                          {
                              deleteTankInstance(a);
                          }
                          else
                          {
                              killTank(a);
                              deadsTanksControl(a);
                          }
                           */
                    }
                }
            }
        }

        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            if (shell2[i] != nullptr)
            {
                shell2[i]->flyStep();
                if (hittingPlayer(i))
                {
                    shell2[i]->explosed = true;
                    tank[0]->hit();
                    if (tank[0]->getArmor() == 0)
                    {
                        gameOver();
                    }
                }
            }
        }

        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            if (shell1[i] != nullptr)
            {
                if (shell1[i]->getExplosed())
                {
                    if (explosionsCount < 10)
                    {
                        explosionsCount++;
                        expl[findFreeExpl()] = new Explosion(shell1[i]->getX(), shell1[i]->getY(), true);
                    }
                    delete shell1[i];
                    shell1[i] = nullptr;
                    tank[0]->cannon1Count--;
                }
            }
        }

        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            if (shell2[i] != nullptr)
            {
                if (shell2[i]->getExplosed())
                {
                    if (explosionsCount < MAX_EXPLOSIONS)
                    {
                        explosionsCount++;
                        expl[findFreeExpl()] = new Explosion(shell2[i]->getX(), shell2[i]->getY(), true);
                    }
                    delete shell2[i];
                    shell2[i] = nullptr;
                    tank[shell2TankNum[i]]->cannon1Count--;
                }
            }
        }

        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            if (shell1[i] != nullptr)
            {
                shell1[i]->setPosLock(false);
            }
        }

        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            if (shell2[i] != nullptr)
            {
                shell2[i]->setPosLock(false);
            }
        }
    }

    byte GameTank::findFreeExpl()
    {
        for (byte i = 0; i < MAX_EXPLOSIONS; i++)
        {
            if (expl[i] == nullptr)
            {
                return i;
            }
        }
        return 254;
    }

    void GameTank::gameStep()
    {

        tank[0]->shootTimer.tick();
        drawScreen();
        portalControl();
        tankControl();
        explosionsControl();
        cannonControl();
        for (byte i = 1; i < MAX_TANK_COUNT; i++)
        {
            if (ai[i] != nullptr)
            {
                ai[i]->steper();
            }
        }
        if (btn_esc.btnState())
        {

            gamePause();
        }
        if (enemysCount < enemysCountOnScreen)
        {
           
            portalCreate();
        }
    }

    void GameTank::killUndDelete(uint8_t tankNum)
    {
        if (ai[tankNum] != nullptr)
        {
            delete ai[tankNum];
            ai[tankNum] = nullptr;
        }
        if (tank[tankNum] != nullptr)
        {
            delete tank[tankNum];
            tank[tankNum] = nullptr;
        }
        enemysCount--;
        score = score + 1 * enemysCountOnScreen;
    }

    bool GameTank::checkCorner(uint8_t corner)
    {
        switch (corner)
        {
        case 0:
            if (tank[0]->getTankXPosition() > 28 /*tank size + 10 px*/)
            {
                return true;
            }
            else if (tank[0]->getTankYPosition() > 28 /*tank size + 10 px*/)
            {
                return true;
            }
            break;
        case 1:
            if (tank[0]->getTankXPosition() < 81 /*127 - tank size- tank size- 10 px*/)
            {
                return true;
            }
            else if (tank[0]->getTankYPosition() > 28 /*tank size + 10 px*/)
            {
                return true;
            }
            break;
        case 2:
            if (tank[0]->getTankXPosition() > 28 /*tank size*/)
            {
                return true;
            }
            else if (tank[0]->getTankYPosition() < 17 /*63 - tank size- tank size- 10 px*/)
            {
                return true;
            }
            break;
        case 3:
            if (tank[0]->getTankXPosition() < 81 /*127 - tank size- tank size- 10 px*/)
            {
                return true;
            }
            else if (tank[0]->getTankYPosition() < 17 /*63 - tank size- tank size- 10 px*/)
            {
                return true;
            }
            break;
        }
        return false;
    }

    /*
        void GameTank::killTank(uint8_t tankNum)
        {
            if (ai[tankNum] != nullptr)
            {
                delete ai[tankNum];
                ai[tankNum] = nullptr;
            }
            enemysCount--;
            tank[tankNum]->setArmor(5);
            score = score + 1 * enemysCountOnScreen;
        }

        void GameTank::deleteTankInstance(uint8_t tankNum)
        {
            delete tank[tankNum];
            tank[tankNum] = nullptr;
            deadsTanksControlAfterDestroy(tankNum);
        }

        void GameTank::deadsTanksControl(uint8_t tankNum)
        {
            if (deadTanks[4] != 0 && deadTanks[0] != 0)
            {
                delete tank[deadTanks[0]];
                tank[deadTanks[0]] = nullptr;
            }
            for (uint8_t i = 1; i < MAX_DEAD_ENEMYES; i++)
            {
                deadTanks[i - 1] = deadTanks[i];
            }
            deadTanks[MAX_DEAD_ENEMYES - 1] = tankNum;
        }

        void GameTank::deadsTanksControlAfterDestroy(uint8_t tankNum)
        {
            uint8_t i;
            for (i = 0; i < MAX_DEAD_ENEMYES; i++)
            {
                if (deadTanks[i] == tankNum)
                {
                    break;
                }
            }
            i++;
            for (i; i < MAX_DEAD_ENEMYES; i++)
            {
                deadTanks[i - 1] = deadTanks[i];
            }
            deadTanks[MAX_DEAD_ENEMYES - 1] = 0;
        }
        */
}