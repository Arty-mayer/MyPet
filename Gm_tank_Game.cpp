
#include "Gm_tank_Game.h"

namespace Tank
{

    Game::Game()
    {
        ai[0] = nullptr;
        for (byte i = 1; i < MAX_TANK_COUNT; i++)
        {

            tank[i] = nullptr;
            ai[i] = nullptr;
        }
        for (byte i = 1; i <= 3; i++)
        {
            tank[i] = new Tank(50, (i - 1) * 20, LEFT, 2, 2);
            ai[i] = new Ai(*tank[i]);
        }
        tank[0] = new Tank(0, 20, RIGHT, 1, 5);
        for (byte i = 0; i < CANNON1_MAX; i++)
        {
            shell1[i] = nullptr;
        }
        tank[0] = new Tank(0, 20, RIGHT, 1, 5);

        for (byte i = 0; i < CANNON2_MAX; i++)
        {
            shell2[i] = nullptr;
        }

        shell1[1] = nullptr;
        for (byte i = 0; i < 10; i++)
        {
            expl[i] = nullptr;
        }
    }

    void Game::mainLoop()
    {
        // btnsListener();
        tank[0]->shootTimer.tick();

        frameTimer.tick();

        if (frameTimer.isTimerEnd())
        {

            frameTimer.timerStart();
            gameStep();
        }
    }

    void Game::drawScreen()
    {
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

        for (byte i = 0; i < 10; i++)
        {
            if (expl[i] != nullptr)
            {
                gfx.drawExplosion(expl[i]->getX(), expl[i]->getY(), expl[i]->getImgNum());
            }
        }
        gfx.drawScr();
    }

    byte Game::findFreeShell(byte max)
    {
        for (byte i = 0; i < max; i++)
        {
            if (shell1[i] == nullptr)
            {
                return i;
            }
        }
        return 254;
    }

    void Game::tankControl()
    {
        if (btn_st.btnState())
        {
            if (tank[0]->shoot())
            {
                byte a = findFreeShell(CANNON1_MAX);
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

    void Game::enemysControl()
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
                        byte a = findFreeShell(20);
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

    bool Game::movmentBlockControl(byte TankNum)
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

    byte Game::hittingEnemys(byte i)
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

    bool Game::hittingPlayer(byte i)
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

    bool Game::checkCollisionU(int x1, int y1, byte size1, int x2, int y2, byte size2)
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
    bool Game::checkCollisionD(int x1, int y1, byte size1, int x2, int y2, byte size2)
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
    bool Game::checkCollisionL(int x1, int y1, byte size1, int x2, int y2, byte size2)
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
    bool Game::checkCollisionR(int x1, int y1, byte size1, int x2, int y2, byte size2)
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

    void Game::explosionsControl()
    {

        for (byte i = 0; i < 10; i++)
        {
            if (expl[i] != nullptr && expl[i]->isFinished())
            {
                delete expl[i];
                expl[i] = nullptr;
                explosionsCount--;
            }
        }
    }

    void Game::cannonControl()
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
                    if (explosionsCount < 10)
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

    byte Game::findFreeExpl()
    {
        for (byte i = 0; i < 10; i++)
        {
            if (expl[i] == nullptr)
            {
                return i;
            }
        }
        return 254;
    }

    void Game::gameStep()
    {
        drawScreen();
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
    }

    void Game::btnsListener()
    {
        btn_lt.buttonListener();
        btn_rt.buttonListener();
        btn_dn.buttonListener();
        btn_up.buttonListener();
        btn_st.buttonListener();
    }

}