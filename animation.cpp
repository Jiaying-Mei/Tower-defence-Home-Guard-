#include "game.h"
#include <QTimer>
#include <string>
#include <sstream>
using namespace std;

class Core;

void checkVictory(Core *aCore) {
    if (aCore->gamemanager->qw.empty()&&aCore->gamemanager->enemymanager->isVectorEmpty())
        aCore->gamemanager->showSettlement("victory");
}

AnimationManager::AnimationManager(Core *aCore) {
    this->core = aCore;
    srand((unsigned int)time(NULL));
    this->isRunning = false;
    this->GameTimer = new QTimer(aCore->menumanager->getView());
    this->GameTimer->setInterval(10);
    aCore->menumanager->getView()->connect(this->GameTimer, &QTimer::timeout, [=]() {
        /*
        string s;
        stringstream ss;
        ss<<aCore->gamemanager->tick;
        ss>>s;
        aCore->menumanager->game_log->setPlainText(s.c_str());
        */
        checkVictory(this->core);
        while (aCore->gamemanager->qw.size()&&aCore->gamemanager->qw.front().time==aCore->gamemanager->tick) {
            int targetroute = aCore->gamemanager->qw.front().route;
            if (targetroute<0||targetroute>=this->core->gamemanager->route_cnt) {
                if (this->core->gamemanager->route_cnt==1)
                    targetroute = 0;
                else
                    targetroute = rand()%this->core->gamemanager->route_cnt;
            }
            aCore->gamemanager->enemymanager->addEnemy(aCore->gamemanager->qw.front().enemytype, targetroute);
            aCore->gamemanager->qw.pop();
            aCore->gamemanager->increaseProgress1();
        }
        aCore->gamemanager->towermanager->run();
        aCore->gamemanager->towermanager->checkTower2();
        aCore->gamemanager->bulletmanager->run();
        aCore->gamemanager->enemymanager->run();
        aCore->gamemanager->hiteffectmanager->run();
        aCore->gamemanager->tick++;
    });
}

void AnimationManager::start() {
    if (!this->isRunning) {
        this->isRunning = true;
        this->GameTimer->start();
    }
}

void AnimationManager::stop() {
    if (this->isRunning) {
        this->isRunning = false;
        this->GameTimer->stop();
    }
}
