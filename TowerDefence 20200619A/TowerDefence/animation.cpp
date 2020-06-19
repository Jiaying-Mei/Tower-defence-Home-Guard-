#include "game.h"
#include <QTimer>
#include <string>
#include <sstream>
using namespace std;

class Core;

AnimationManager::AnimationManager(Core *aCore) {
    this->core = aCore;
    this->isRunning = false;
    this->GameTimer = new QTimer(aCore->menumanager->getView());
    this->GameTimer->setInterval(10);
    aCore->menumanager->getView()->connect(this->GameTimer, &QTimer::timeout, [=]() {

        string s;
        stringstream ss;
        ss<<aCore->gamemanager->tick;
        ss>>s;
        aCore->menumanager->game_log->setPlainText(s.c_str());

        while (aCore->gamemanager->qw.size()&&aCore->gamemanager->qw.front().time==aCore->gamemanager->tick) {
            aCore->gamemanager->enemymanager->addEnemy(aCore->gamemanager->qw.front().enemytype, aCore->gamemanager->qw.front().route);
            aCore->gamemanager->qw.pop();
        }
        aCore->gamemanager->enemymanager->run();
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
