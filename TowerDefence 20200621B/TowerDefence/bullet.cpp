#define halfBulletWidth 20
#define halfBulletHeight 20

#include "game.h"
#include "audio.h"
#include <cmath>
#include <QDebug>
#include <queue>
using namespace std;

class Core;

void Bullet::init(Core *aCore, int towerid, AcidPoint targetAcidPoint) {
    if (this->type=="bullet21") {
        this->fpos->x = targetAcidPoint.x;
        this->fpos->y = targetAcidPoint.y;
        this->tpos->x = targetAcidPoint.x;
        this->tpos->y = targetAcidPoint.y;
        return;
    }
    this->fpos->x = aCore->gamemanager->towerscenter[towerid].x;
    this->fpos->y = aCore->gamemanager->towerscenter[towerid].y;
    double k = 1.*this->speed*this->mtick/sqrt((targetAcidPoint.x-fpos->x)*(targetAcidPoint.x-fpos->x)+(targetAcidPoint.y-fpos->y)*(targetAcidPoint.y-fpos->y));
    this->tpos->x = fpos->x+(int)((targetAcidPoint.x-fpos->x)*k);
    this->tpos->y = fpos->y+(int)((targetAcidPoint.y-fpos->y)*k);
}

void Bullet::move() {
    this->ntick++;
}

void Bullet::remove(Core *aCore) {
    aCore->menumanager->GameScene.removeItem(this->getItem());
}

void Bullet::refreshB(Core *aCore) {
    this->refresh((int)((this->fpos->x+(1.*this->ntick/this->mtick)*(tpos->x-fpos->x))*aCore->conf->nowwratio), (int)((this->fpos->y+(1.*this->ntick/this->mtick)*(tpos->y-fpos->y))*aCore->conf->nowhratio), aCore->conf->ggame->bullet_width, aCore->conf->ggame->bullet_height);
}

bool Bullet::isOverRange() {
    return this->ntick>this->mtick;
}

int Bullet::getDamage() {
    return this->damage;
}

int Bullet::getFrozen() {
    return this->frozen;
}

AcidPoint Bullet::getCenter() {
    return AcidPoint(this->fpos->x+(1.*this->ntick/this->mtick)*(tpos->x-fpos->x)+halfBulletWidth, this->fpos->y+(1.*this->ntick/this->mtick)*(tpos->y-fpos->y)+halfBulletHeight);
}

bool Bullet::isHit(Core *aCore, Enemy* e) {
    AcidPoint tmpap1 = this->getCenter();
    AcidPoint tmpap2 = e->getCenter(aCore);
    return (tmpap1.x-tmpap2.x)*(tmpap1.x-tmpap2.x)+(tmpap1.y-tmpap2.y)*(tmpap1.y-tmpap2.y)<=this->hitdistance*this->hitdistance;
}

void Bullet::setNTick(int tntick) {
    this->ntick = tntick;
}

void BulletManager::setCore(Core *aCore) {
    this->core = aCore;
}

void BulletManager::removeAllBullets() {
    for (Bullet* b:this->bullets)
        if (b) {
            b->remove(this->core);
            delete b;
        }
    this->bullets.clear();
}

Bullet* BulletManager::getBullet11(int towerid, AcidPoint targetAP) {
    Bullet *tmp = new Bullet(this->core->conf->bsi->bullet11, &this->core->menumanager->GameScene, 0, 0, this->core->conf->ggame->bullet_width, this->core->conf->ggame->bullet_height);
    tmp->init(this->core, towerid, targetAP);
    return tmp;
}

Bullet* BulletManager::getBullet12(int towerid, AcidPoint targetAP) {
    Bullet *tmp = new Bullet(this->core->conf->bsi->bullet12, &this->core->menumanager->GameScene, 0, 0, this->core->conf->ggame->bullet_width, this->core->conf->ggame->bullet_height);
    tmp->init(this->core, towerid, targetAP);
    return tmp;
}

Bullet* BulletManager::getBullet21(int towerid, AcidPoint targetAP) {
    Bullet *tmp = new Bullet(this->core->conf->bsi->bullet21, &this->core->menumanager->GameScene, 0, 0, this->core->conf->ggame->bullet_width, this->core->conf->ggame->bullet_height);
    tmp->init(this->core, towerid, targetAP);
    return tmp;
}

Bullet* BulletManager::getBullet31(int towerid, AcidPoint targetAP) {
    Bullet *tmp = new Bullet(this->core->conf->bsi->bullet31, &this->core->menumanager->GameScene, 0, 0, this->core->conf->ggame->bullet_width, this->core->conf->ggame->bullet_height);
    tmp->init(this->core, towerid, targetAP);
    return tmp;
}

Bullet* BulletManager::getBullet32(int towerid, AcidPoint targetAP) {
    Bullet *tmp = new Bullet(this->core->conf->bsi->bullet32, &this->core->menumanager->GameScene, 0, 0, this->core->conf->ggame->bullet_width, this->core->conf->ggame->bullet_height);
    tmp->init(this->core, towerid, targetAP);
    return tmp;
}

Bullet* BulletManager::getBullet33(int towerid, AcidPoint targetAP) {
    Bullet *tmp = new Bullet(this->core->conf->bsi->bullet33, &this->core->menumanager->GameScene, 0, 0, this->core->conf->ggame->bullet_width, this->core->conf->ggame->bullet_height);
    tmp->init(this->core, towerid, targetAP);
    return tmp;
}

Bullet* BulletManager::getBullet(string bulletname, int towerid, AcidPoint targetAP) {
    if (bulletname=="bullet11")
        return this->getBullet11(towerid, targetAP);
    if (bulletname=="bullet12")
        return this->getBullet12(towerid, targetAP);
    if (bulletname=="bullet21")
        return this->getBullet21(towerid, targetAP);
    if (bulletname=="bullet31")
        return this->getBullet31(towerid, targetAP);
    if (bulletname=="bullet32")
        return this->getBullet32(towerid, targetAP);
    if (bulletname=="bullet33")
        return this->getBullet33(towerid, targetAP);
    return this->getBullet11(towerid, targetAP);
}

void BulletManager::addBullet11(string bulletname, int towerid, AcidPoint targetAP) {
    if (bulletname=="bullet11"||bulletname=="bullet12") this->core->audiomanager->playTower1();
    if (bulletname=="bullet21") this->core->audiomanager->playTower2();
    if (bulletname=="bullet31"||bulletname=="bullet32"||bulletname=="bullet33") this->core->audiomanager->playTower2();
    if (bulletname=="bullet32") {
        Bullet* xtmp = this->getBullet(bulletname, towerid, targetAP);
        xtmp->setNTick(3);
        this->bullets.push_back(xtmp);
    }
    Bullet* tmp = this->getBullet(bulletname, towerid, targetAP);
    this->bullets.push_back(tmp);
}

void BulletManager::checkHit() {
    if (this->bullets.empty()) return;
    queue<Bullet*> tmp;
    while (tmp.size()) tmp.pop();
    for (Bullet* b:this->bullets)
        if (b) {
            vector<Enemy*> *ve = this->core->gamemanager->enemymanager->getEnemies();
            bool flag = true;
            for (Enemy* e:*ve)
                //if (e&&b->getItem()->collidesWithItem(e->getItem())) {
                if (e&&b->isHit(this->core, e)) {
                    e->addFrozenDuration(b->getFrozen());
                    e->takeHP(b->getDamage());
                    b->remove(this->core);
                    delete b;
                    flag = false;
                    break;
                }
            if (flag)
                tmp.push(b);
        }
    if (tmp.size()==this->bullets.size()) return;
    this->bullets.clear();
    if (tmp.empty()) return;
    while (tmp.size()) {
        this->bullets.push_back(tmp.front());
        tmp.pop();
    }
}

void BulletManager::run() {
    this->checkHit();
    if (this->bullets.empty()) return;
    queue<Bullet*> tmp;
    while (tmp.size()) tmp.pop();
    for (Bullet* b:this->bullets)
        if (b) {
            b->move();
            if (b->isOverRange()) {
                b->remove(this->core);
                delete b;
            } else {
                tmp.push(b);
                b->refreshB(this->core);
            }
        }
    if (tmp.size()==this->bullets.size()) return;
    this->bullets.clear();
    if (tmp.empty()) return;
    while (tmp.size()) {
        this->bullets.push_back(tmp.front());
        tmp.pop();
    }
}

void BulletManager::refreshAllBullets() {
    for (Bullet* b:this->bullets)
        if (b)
            b->refreshB(this->core);
}
