#include "game.h"
#include <QDebug>

string Tower::getType() {
    return this->type;
}

string Tower::getBulletName() {
    return this->bulletname;
}

int Tower::getLevel() {
    return this->level;
}

int Tower::getRange(Core *aCore) {
    return aCore->conf->bsi->getBullet(aCore->conf->tsi->getTower(this->type)->bullet[this->level-1])->getRange();
}

void Tower::setTower(string towertype, string towerimageurl, int towerlevel, int towercooldown, string towerbulletname) {
    this->type = towertype;
    this->setPixmap(towerimageurl);
    this->level = towerlevel;
    this->cooldown = towercooldown;
    this->bulletname = towerbulletname;
}

bool Tower::isReady() {
    return this->nowtick==0;
}

void Tower::decreaseNowTick() {
    if (this->nowtick>0)
        this->nowtick--;
}

void Tower::resetNowTick() {
    this->nowtick = this->cooldown;
}

void Tower::refreshRangeAB(Core *aCore, AcidPoint tcap) {
    if (!aCore->gamemanager->getIsShowRange()||this->type=="None"||this->level==0) {
        this->rangeab->getItem()->setZValue(-1);
        return;
    }
    this->rangeab->getItem()->setZValue(0);
    int tr = this->getRange(aCore);
    this->rangeab->refresh((int)((tcap.x-tr)*aCore->conf->nowwratio), (int)((tcap.y-tr)*aCore->conf->nowhratio), (int)(tr*2*aCore->conf->nowwratio), (int)(tr*2*aCore->conf->nowhratio));
}

AcidButton* Tower::getRangeAB() {
    return this->rangeab;
}

void TowerManager::setCore(Core *aCore) {
    this->core = aCore;
}

void TowerManager::clear() {
    for (auto it = this->towers.begin(); it!=towers.end(); it++) {
        auto tmp = (*it);
        if (tmp) {
            this->core->menumanager->GameScene.removeItem(tmp->getItem());
            this->core->menumanager->GameScene.removeItem(tmp->getRangeAB()->getItem());
            free(tmp->getRangeAB());
        }
        free(tmp);
    }
    towers.clear();
}

void TowerManager::run() {
    for (Tower* t:this->towers)
        t->decreaseNowTick();
}

bool isEInRange(AcidPoint p1, AcidPoint p2, int range) {
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)<=range*range;
}

void TowerManager::checkTower2() {
    for (int i=0; i<this->core->gamemanager->getTowerCnt(); i++) {
        Tower* t = this->towers[i];
        if (t->getType()=="Tower2"&&t->isReady()) {
            bool flag = false;
            for (Enemy* e:*this->core->gamemanager->enemymanager->getEnemies())
                if (isEInRange(this->core->gamemanager->towerscenter[i], e->getCenter(this->core), t->getRange(this->core))) {
                    flag = true;
                    this->core->gamemanager->bulletmanager->addBullet(t->getBulletName(), i, e->getCenter(this->core));
                    this->core->gamemanager->animationmanager->addCircularAnimation("tower2ca", this->core->gamemanager->towerscenter[i].x, this->core->gamemanager->towerscenter[i].y);
                }
            if (flag)
                t->resetNowTick();
        }
    }
}
