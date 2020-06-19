#include "game.h"

string Tower::getType() {
    return this->type;
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

void TowerManager::setCore(Core *aCore) {
    this->core = aCore;
}

void TowerManager::clear() {
    for (auto it = this->towers.begin(); it!=towers.end(); it++) {
        auto tmp = (*it);
        if (tmp) this->core->menumanager->GameScene.removeItem(tmp->getItem());
        free(tmp);
    }
    towers.clear();
}
