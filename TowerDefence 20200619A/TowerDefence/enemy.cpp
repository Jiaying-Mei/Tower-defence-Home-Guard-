#include "game.h"
#include <QDebug>

void Enemy::setRoute(int troute) {
    this->route = troute;
}

void Enemy::move() {
    if (this->frozen) {
        this->frozen--;
        return;
    }
    this->pos+=speed;
}

bool Enemy::takeHP(int tdamage) {
    if (this->HP<=0) return false;
    this->HP-=tdamage;
    if (this->HP<0) this->HP = 0;
    return true;
}

void Enemy::addFrozenDuration(int tDuration) {
    this->frozen += tDuration;
}

bool Enemy::isDied() {
    return this->HP<=0;
}

int Enemy::getReward() {
    return this->reward;
}

int Enemy::getDamage() {
    return this->damage;
}

bool Enemy::refreshE(Core *aCore) {
    AcidPoint tmpap = aCore->gamemanager->getPos(this->route, this->pos);
    if (tmpap.x==-1&&tmpap.y==-1) return false;
    this->refresh((int)(tmpap.x*aCore->conf->nowwratio), (int)(tmpap.y*aCore->conf->nowhratio), aCore->conf->ggame->enemy_width, aCore->conf->ggame->enemy_height);
    return true;
}

void Enemy::remove(Core *aCore) {
    aCore->menumanager->GameScene.removeItem(this->getItem());
}

void EnemyManager::setCore(Core *aCore) {
    this->core = aCore;
}

Enemy* EnemyManager::getEnemy1() {
    Enemy *tmp = new Enemy("Enemy1", this->core->conf->esi->enemy1->health, this->core->conf->esi->enemy1->speed, 0, this->core->conf->esi->enemy1->reward, this->core->conf->esi->enemy1->damage, this->core->conf->esi->enemy1->imageurl, &this->core->menumanager->GameScene, 2, 2, this->core->conf->ggame->enemy_width, this->core->conf->ggame->enemy_height);
    //this->core->menumanager->GameScene.removeItem(tmp.getItem());
    return tmp;
}

Enemy* EnemyManager::getEnemy2() {
    Enemy *tmp = new Enemy("Enemy2", this->core->conf->esi->enemy2->health, this->core->conf->esi->enemy2->speed, 0, this->core->conf->esi->enemy2->reward, this->core->conf->esi->enemy2->damage, this->core->conf->esi->enemy2->imageurl, &this->core->menumanager->GameScene, 2, 2, this->core->conf->ggame->enemy_width, this->core->conf->ggame->enemy_height);
    return tmp;
}

Enemy* EnemyManager::getEnemy3() {
    Enemy *tmp = new Enemy("Enemy3", this->core->conf->esi->enemy3->health, this->core->conf->esi->enemy3->speed, 0, this->core->conf->esi->enemy3->reward, this->core->conf->esi->enemy3->damage, this->core->conf->esi->enemy3->imageurl, &this->core->menumanager->GameScene, 2, 2, this->core->conf->ggame->enemy_width, this->core->conf->ggame->enemy_height);
    return tmp;
}

Enemy* EnemyManager::getEnemy(string enemytype) {
    if (enemytype == "Enemy1") return this->getEnemy1();
    if (enemytype == "Enemy2") return this->getEnemy2();
    if (enemytype == "Enemy3") return this->getEnemy3();
    return this->getEnemy1();
}

void EnemyManager::removeAllEnemies() {
    for (vector<Enemy*>::iterator it = this->enemies.begin(); it!= this->enemies.end(); it++) {
        (*it)->remove(this->core);
        delete *it;
    }
    this->enemies.clear();
}

void EnemyManager::addEnemy(string enemytype, int route) {
    Enemy *tmp = getEnemy(enemytype);
    tmp->setRoute(route);
    tmp->refreshE(this->core);
    this->enemies.push_back(tmp);
}

void EnemyManager::checkHP() {
    queue<Enemy*> tmp;
    while (tmp.size()) tmp.pop();
    for (Enemy* e:this->enemies)
        if (e->isDied()) {
            e->remove(this->core);
            this->core->gamemanager->giveCoin(e->getReward());
            delete e;
        } else
            tmp.push(e);
    if (tmp.empty()) return;
    this->enemies.clear();
    while (tmp.size()) {
        enemies.push_back(tmp.front());
        tmp.pop();
    }
}

void EnemyManager::run() {
    if (this->enemies.empty()) return;
    this->checkHP();
    queue<Enemy*> tmp;
    while (tmp.size()) tmp.pop();
    for (Enemy* e:this->enemies) {
        e->move();
        if (!e->refreshE(this->core)) {
            e->remove(this->core);
            if (this->core->gamemanager->hasHealth(e->getDamage()))
                this->core->gamemanager->takeHealth(e->getDamage());
            else {
                this->core->gamemanager->setHealth(0);
                this->core->gamemanager->showSettlement("defeat");
            }
            delete e;
        } else
            tmp.push(e);
    }
    if (tmp.size()==this->enemies.size()) return;
    this->enemies.clear();
    if (tmp.empty()) return;
    while (tmp.size()) {
        enemies.push_back(tmp.front());
        tmp.pop();
    }
}

void EnemyManager::refreshAllEnemies() {
    for (Enemy* e:this->enemies)
        if (e)
            e->refreshE(this->core);
}
