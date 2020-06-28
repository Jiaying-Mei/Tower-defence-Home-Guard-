#include "game.h"
#include "audio.h"
#include <QTimer>
#include <string>
#include <sstream>
using namespace std;

class Core;

void checkVictory(Core *aCore) {
    if (aCore->gamemanager->qw.empty()&&aCore->gamemanager->enemymanager->isVectorEmpty())
        aCore->gamemanager->showSettlement("victory");
}

void CircularAnimation::remove(Core *aCore) {
    aCore->menumanager->GameScene.removeItem(this->getItem());
}

void CircularAnimation::increaseNowTick() {
    this->nowtick++;
}

bool CircularAnimation::isDurationExceeded() {
    return this->nowtick>=this->duration;
}

void CircularAnimation::refreshCA() {
    int tmp_x, tmp_y, tmp_r, tmp_d;
    tmp_r = this->initR+(int)(this->deltaR*1.*this->nowtick/this->duration);
    tmp_x = this->center->x-tmp_r;
    tmp_y = this->center->y-tmp_r;
    tmp_d = tmp_r*2;
    this->refresh((int)(tmp_x*this->co->nowwratio), (int)(tmp_y*this->co->nowhratio), (int)(tmp_d*this->co->nowwratio), (int)(tmp_d*this->co->nowhratio));
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
            if (aCore->gamemanager->qw.front().enemytype=="ZombieComingEffect") {
                aCore->gamemanager->qw.pop();
                aCore->audiomanager->playZombieComing();
                continue;
            }
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
        this->runAllCircularAnimations();
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

void AnimationManager::addCircularAnimation(string targetcircularanimation, int p_x, int p_y) {
    if (targetcircularanimation=="tower2ca") {
        CircularAnimation *tmp = new CircularAnimation(this->core->conf, this->core->conf->cai->tower2cad, &this->core->menumanager->GameScene, p_x, p_y);
        cas.push_back(tmp);
        tmp->refreshCA();
    }
}

void AnimationManager::removeAllCircularAnimations() {
    for (vector<CircularAnimation*>::iterator it = this->cas.begin(); it!= this->cas.end(); it++) {
        (*it)->remove(this->core);
        delete *it;
    }
    this->cas.clear();
}

void AnimationManager::refreshAllCircularAnimations() {
    for (CircularAnimation *ca:this->cas)
        if (ca)
            ca->refreshCA();
}

void AnimationManager::runAllCircularAnimations() {
    if (this->cas.empty()) return;
    queue<CircularAnimation*> tmp;
    while (tmp.size()) tmp.pop();
    for (CircularAnimation* ca:this->cas)
        if (ca) {
            ca->increaseNowTick();
            if (ca->isDurationExceeded()) {
                ca->remove(this->core);
                delete ca;
            } else {
                ca->refreshCA();
                tmp.push(ca);
            }
        }
    if (tmp.size()==this->cas.size()) return;
    this->cas.clear();
    if (tmp.empty()) return;
    while (tmp.size()) {
        this->cas.push_back(tmp.front());
        tmp.pop();
    }
}
