#include "game.h"
#include "menu.h"
#include "config.h"
#include "audio.h"
#include <QGraphicsRectItem>
#include <QDebug>
#include "string"
#include "sstream"
using namespace std;

GameManager::GameManager() {
    this->level = "level-1";
    this->isPaused = true;
    this->isLoading = true;
    this->isInSettlement = false;
    this->isBTShowed = false;
    this->isUpgradeShowed = false;
    this->isRemoveShowed = false;
    this->selection = -1;
    this->isShowRange = false;
    this->towermanager = new TowerManager;
    this->enemymanager = new EnemyManager;
    this->bulletmanager = new BulletManager;
    this->hiteffectmanager = new HitEffectManager;
}

void GameManager::setCore(Core *aCore) {
    this->core = aCore;
    this->towermanager->setCore(aCore);
    this->enemymanager->setCore(aCore);
    this->bulletmanager->setCore(aCore);
    this->hiteffectmanager->setCore(aCore);
    this->animationmanager = new AnimationManager(aCore);
    this->selection_width = &aCore->conf->ggame->selection_width;
    this->selection_height = &aCore->conf->ggame->selection_height;
}

void GameManager::loadLevel1() {
    this->core->menumanager->buttonmanager->getGameBackground()->setPixmap(this->core->pathprefix + "image/level1map.jpg");
    this->initialcoin = &this->core->conf->gl1->initialcoin;
    this->initialhealth = &this->core->conf->gl1->initialhealth;
    this->tower_cnt = &this->core->conf->gl1->tower_cnt;
    this->tower_width = &this->core->conf->gl1->tower_width;
    this->tower_height = &this->core->conf->gl1->tower_height;
    this->towers_x = this->core->conf->gl1->tower_x;
    this->towers_y = this->core->conf->gl1->tower_y;
    this->towerscenter = this->core->conf->gl1->towerscenter;
    for (vector<Wave>::iterator it=this->core->conf->gl1->waves.begin();it!=this->core->conf->gl1->waves.end();it++) {
        this->qw.push(*it);
        if ((*it).enemytype!="ZombieComingEffect")
            this->progress_2++;
    }
    this->route_cnt = 1;
}

void GameManager::loadLevel2() {
    this->core->menumanager->buttonmanager->getGameBackground()->setPixmap(this->core->pathprefix + "image/level2map.jpg");
    this->initialcoin = &this->core->conf->gl2->initialcoin;
    this->initialhealth = &this->core->conf->gl2->initialhealth;
    this->tower_cnt = &this->core->conf->gl2->tower_cnt;
    this->tower_width = &this->core->conf->gl2->tower_width;
    this->tower_height = &this->core->conf->gl2->tower_height;
    this->towers_x = this->core->conf->gl2->tower_x;
    this->towers_y = this->core->conf->gl2->tower_y;
    this->towerscenter = this->core->conf->gl2->towerscenter;
    for (vector<Wave>::iterator it=this->core->conf->gl2->waves.begin();it!=this->core->conf->gl2->waves.end();it++) {
        this->qw.push(*it);
        if ((*it).enemytype!="ZombieComingEffect")
            this->progress_2++;
    }
    this->route_cnt = 2;
}

void GameManager::loadLevel(string levelname) {
    if (!this->isPaused) this->toggleCP();
    if (this->isInSettlement) this->hideSettlement();
    if (this->isBTShowed) this->hideBT();
    if (this->isUpgradeShowed) this->hideUpgrade();
    if (this->isRemoveShowed) this->hideRemove();
    this->tick=0;
    while (this->qw.size()) qw.pop();
    this->enemymanager->removeAllEnemies();
    this->bulletmanager->removeAllBullets();
    this->hiteffectmanager->removeAllHitEffects();
    this->animationmanager->removeAllCircularAnimations();
    this->progress_1 = 0;
    this->progress_2 = 0;
    if (levelname=="level-1") {
        this->isLoading = true;
        this->level = "level-1";
        loadLevel1();
    } else if (levelname=="level-2") {
        this->isLoading = true;
        this->level = "level-2";
        loadLevel2();
    } else
        return;
    this->setCoin(*this->initialcoin);
    this->setHealth(*this->initialhealth);
    this->setSelection(-1);
    this->core->gamemanager->towermanager->clear();
    for (int i = 0; i < *this->tower_cnt; i++) {
        Tower *tmp = new Tower("game tower", this->core->pathprefix + "image/towerposition.png", &this->core->menumanager->GameScene, this->towers_x[i], this->towers_y[i], *this->tower_width, *this->tower_height);
        tmp->setTower("None", this->core->pathprefix + "image/towerposition.png", 0, 99999999, "None");
        this->towermanager->towers.push_back(tmp);
    }
    this->core->menumanager->game_log->setPlainText("Please click on the dotted box to grow plants!");
    this->core->menumanager->showGame();
    this->refreshProgressBar();
    this->isLoading = false;
}

void GameManager::toggleCP() {
    if (this->isPaused) {
        this->isPaused = false;
        //开启计时器
        this->animationmanager->start();
        this->core->menumanager->buttonmanager->getGameCP()->setPixmap(this->core->pathprefix + "image/pause icon.png");
    } else {
        this->isPaused = true;
        //关闭计时器
        this->animationmanager->stop();
        this->core->menumanager->buttonmanager->getGameCP()->setPixmap(this->core->pathprefix + "image/continue icon.png");
    }
}

void GameManager::reloadLevel() {
    this->loadLevel(this->level);
}

void GameManager::setCoin(int c) {
    this->coin = c;
    string s;
    stringstream ss;
    ss.clear();
    ss<<c;
    ss>>s;
    this->core->menumanager->game_cointext->setPlainText(s.c_str());
}

bool GameManager::hasCoin(int c) {
    return this->coin>=c;
}

void GameManager::giveCoin(int c) {
    this->setCoin(this->coin+c);
}

void GameManager::takeCoin(int c) {
    this->setCoin((this->coin-c));
}

int GameManager::getCoin() {
    return this->coin;
}

void GameManager::setHealth(int h) {
    this->health = h;
    string s;
    stringstream ss;
    ss.clear();
    ss<<h;
    ss>>s;
    this->core->menumanager->game_healthtext->setPlainText(s.c_str());
}

bool GameManager::hasHealth(int h) {
    return this->health>=h;
}

void GameManager::giveHealth(int h) {
    this->setHealth(this->health+h);
}

void GameManager::takeHealth(int h) {
    this->setHealth(this->health-h);
}

int GameManager::getHealth() {
    return this->health;
}

void GameManager::setSelection(int targetSelection) {
    if (this->selection!=-1) this->hideSelection();
    if (targetSelection<0||targetSelection>=*this->tower_cnt) {
        this->selection = -1;
        return;
    }
    this->selection = targetSelection;
    this->showSelection();
}

void GameManager::initSelection() {
    if (this->selection!=-1) {
        this->selection = -1;
        this->hideSelection();
    }
}

int GameManager::getSelection() {
    return this->selection;
}

int GameManager::getTowerID(QGraphicsItem *citem) {
    if (this->isLoading) return -1;
    if (*this->tower_cnt!=(int)this->towermanager->towers.size()) return -1;
    for (int i = 0; i < *this->tower_cnt; i++)
        if (this->towermanager->towers[i]->isEqual(citem))
            return i;
    return -1;
}

void GameManager::showSelection() {
    this->selection_x = -this->core->conf->ggame->selection_dx+this->towers_x[this->selection];
    this->selection_y = -this->core->conf->ggame->selection_dy+this->towers_y[this->selection];
    this->core->menumanager->buttonmanager->getGameSelection()->refresh(selection_x, selection_y, *selection_width, *selection_height);
    this->core->menumanager->GameScene.addItem(this->core->menumanager->buttonmanager->getGameSelection()->getItem());
    if (this->core->gamemanager->towermanager->towers[this->selection]->getType()=="None") {
        this->showBT();
        this->core->menumanager->game_log->setPlainText("Mushroom: 50 Sunflower：100 PeaShooter：50");
    } else {
        if (this->core->conf->tsi->getTower(this->core->gamemanager->towermanager->towers[this->selection]->getType())->maxlevel!=this->core->gamemanager->towermanager->towers[this->selection]->getLevel())
            this->showUpgrade();
        this->showRemove();
        this->core->menumanager->game_log->setPlainText(this->core->conf->tsi->getTower(this->core->gamemanager->towermanager->towers[this->selection]->getType())->info[this->core->gamemanager->towermanager->towers[this->selection]->getLevel()-1].c_str());
    }
}

void GameManager::hideSelection() {
    this->core->menumanager->GameScene.removeItem(this->core->menumanager->buttonmanager->getGameSelection()->getItem());
    this->core->menumanager->game_log->setPlainText("");
    if (this->isBTShowed) this->hideBT();
    if (this->isUpgradeShowed) this->hideUpgrade();
    if (this->isRemoveShowed) this->hideRemove();
}

void GameManager::showSettlement(string result) {
    this->isInSettlement = true;
    if (!this->isPaused) this->toggleCP();
    if (result=="victory") {
        this->core->menumanager->buttonmanager->getGameWL()->setPixmap(this->core->pathprefix + "image/win.png");
        this->core->audiomanager->playWin();
        if (this->level=="level-1")
            this->core->menumanager->buttonmanager->hideLock(this->core);
    } else {
        this->core->menumanager->buttonmanager->getGameWL()->setPixmap(this->core->pathprefix + "image/lost.png");
        this->core->audiomanager->playLose();
    }
    this->core->menumanager->GameScene.addItem(this->core->menumanager->buttonmanager->getGameWL()->getItem());
    this->core->menumanager->buttonmanager->getGameWL()->refresh(this->core->conf->ggame->wl_x, this->core->conf->ggame->wl_y, this->core->conf->ggame->wl_width, this->core->conf->ggame->wl_height);
}

void GameManager::hideSettlement() {
    this->isInSettlement = false;
    this->core->menumanager->GameScene.removeItem(this->core->menumanager->buttonmanager->getGameWL()->getItem());
}

bool GameManager::getIsInSettlement() {
    return this->isInSettlement;
}

void refreshBT(Core *aCore) {
    aCore->menumanager->buttonmanager->getGameBT1()->refresh(aCore->conf->ggame->bt1_x, aCore->conf->ggame->bt1_y, aCore->conf->ggame->bt1_width, aCore->conf->ggame->bt1_height);
    aCore->menumanager->buttonmanager->getGameBT2()->refresh(aCore->conf->ggame->bt2_x, aCore->conf->ggame->bt2_y, aCore->conf->ggame->bt2_width, aCore->conf->ggame->bt2_height);
    aCore->menumanager->buttonmanager->getGameBT3()->refresh(aCore->conf->ggame->bt3_x, aCore->conf->ggame->bt3_y, aCore->conf->ggame->bt3_width, aCore->conf->ggame->bt3_height);
}

void refreshUpgrade(Core *aCore) {
    aCore->menumanager->buttonmanager->getGameUpgrade()->refresh(aCore->conf->ggame->upgrade_x, aCore->conf->ggame->upgrade_y, aCore->conf->ggame->upgrade_width, aCore->conf->ggame->upgrade_height);
}

void refreshRemove(Core *aCore) {
    aCore->menumanager->buttonmanager->getGameRemove()->refresh(aCore->conf->ggame->remove_x, aCore->conf->ggame->remove_y, aCore->conf->ggame->remove_width, aCore->conf->ggame->remove_height);
}

void GameManager::showBT() {
    if (this->isBTShowed) return;
    this->isBTShowed = true;
    refreshBT(this->core);
    this->core->menumanager->GameScene.addItem(this->core->menumanager->buttonmanager->getGameBT1()->getItem());
    this->core->menumanager->GameScene.addItem(this->core->menumanager->buttonmanager->getGameBT2()->getItem());
    this->core->menumanager->GameScene.addItem(this->core->menumanager->buttonmanager->getGameBT3()->getItem());
}

void GameManager::hideBT() {
    if (!this->isBTShowed) return;
    this->isBTShowed = false;
    this->core->menumanager->GameScene.removeItem(this->core->menumanager->buttonmanager->getGameBT1()->getItem());
    this->core->menumanager->GameScene.removeItem(this->core->menumanager->buttonmanager->getGameBT2()->getItem());
    this->core->menumanager->GameScene.removeItem(this->core->menumanager->buttonmanager->getGameBT3()->getItem());
}

bool GameManager::getIsBTShowed() {
    return this->isBTShowed;
}

void GameManager::showUpgrade() {
    if (this->isUpgradeShowed) return;
    this->isUpgradeShowed = true;
    refreshUpgrade(this->core);
    this->core->menumanager->GameScene.addItem(this->core->menumanager->buttonmanager->getGameUpgrade()->getItem());
}

void GameManager::hideUpgrade() {
    if (!this->isUpgradeShowed) return;
    this->isUpgradeShowed = false;
    this->core->menumanager->GameScene.removeItem(this->core->menumanager->buttonmanager->getGameUpgrade()->getItem());
}

bool GameManager::getIsUpgradeShowed() {
    return this->isUpgradeShowed;
}

void GameManager::showRemove() {
    if (this->isRemoveShowed) return;
    this->isRemoveShowed = true;
    refreshRemove(this->core);
    this->core->menumanager->GameScene.addItem(this->core->menumanager->buttonmanager->getGameRemove()->getItem());
}

void GameManager::hideRemove() {
    if (!this->isRemoveShowed) return;
    this->isRemoveShowed = false;
    this->core->menumanager->GameScene.removeItem(this->core->menumanager->buttonmanager->getGameRemove()->getItem());
}

bool GameManager::getIsRemoveShowed() {
    return this->isRemoveShowed;
}

AcidPoint GameManager::getPos(int troute, int tpos) {
    if (this->level=="level-1") return this->core->conf->gl1->getPos(troute, tpos);
    if (this->level=="level-2") return this->core->conf->gl2->getPos(troute, tpos);
    return AcidPoint(-1, -1);
}

int GameManager::getTowerCnt() {
    return *this->tower_cnt;
}

void GameManager::increaseProgress1() {
    this->progress_1++;
    if (this->progress_1>this->progress_2)
        this->progress_1 = this->progress_2;
    this->refreshProgressBar();
}

void GameManager::refreshProgressBar() {
    if (this->progress_2==0) {
        this->core->menumanager->buttonmanager->getGameProgressBarInside()->refresh(this->core->conf->ggame->progressbarinside_x, this->core->conf->ggame->progressbarinside_y, this->core->conf->ggame->progressbarinside_width, this->core->conf->ggame->progressbarinside_height);
        this->core->menumanager->buttonmanager->getGameProgressBarHead()->refresh(this->core->conf->ggame->progressbarinside_x+this->core->conf->ggame->progressbarinside_width-this->core->conf->ggame->progressbarhead_dx, this->core->conf->ggame->progressbarhead_y, this->core->conf->ggame->progressbarhead_width, this->core->conf->ggame->progressbarhead_height);
        return;
    }
    double process = 1.*this->progress_1/this->progress_2;
    this->core->menumanager->buttonmanager->getGameProgressBarInside()->refresh(this->core->conf->ggame->progressbarinside_x, this->core->conf->ggame->progressbarinside_y, (int)(this->core->conf->ggame->progressbarinside_width*process)+1, this->core->conf->ggame->progressbarinside_height);
    this->core->menumanager->buttonmanager->getGameProgressBarHead()->refresh(this->core->conf->ggame->progressbarinside_x+(int)(this->core->conf->ggame->progressbarinside_width*process)-this->core->conf->ggame->progressbarhead_dx, this->core->conf->ggame->progressbarhead_y, this->core->conf->ggame->progressbarhead_width, this->core->conf->ggame->progressbarhead_height);
}

void GameManager::refreshSelectedTowerRangeAB() {
    if (this->selection<0) return;
    if (this->level=="level-1")
        this->towermanager->towers[this->selection]->refreshRangeAB(this->core, this->core->conf->gl1->towerscenter[this->selection]);
    else
        this->towermanager->towers[this->selection]->refreshRangeAB(this->core, this->core->conf->gl2->towerscenter[this->selection]);
}

bool GameManager::getIsShowRange() {
    return this->isShowRange;
}

void GameManager::toggleIsShowRange() {
    if (this->isShowRange) {
        this->isShowRange = false;
        this->core->menumanager->buttonmanager->getGameRangeOF()->setPixmap(":/image/rangeoff.png");
    } else {
        this->isShowRange = true;
        this->core->menumanager->buttonmanager->getGameRangeOF()->setPixmap(":/image/rangeon.png");
    }
    for (int i = 0; i < *this->tower_cnt; i++)
        if (this->level=="level-1")
            this->towermanager->towers[i]->refreshRangeAB(this->core, this->core->conf->gl1->towerscenter[i]);
        else
            this->towermanager->towers[i]->refreshRangeAB(this->core, this->core->conf->gl2->towerscenter[i]);
}

void GameManager::refresh() {
    if (this->isLoading) return;
    if (*this->tower_cnt!=(int)this->towermanager->towers.size()) return;
    for (int i = 0; i < *this->tower_cnt; i++) {
        this->towermanager->towers[i]->refresh(this->towers_x[i], this->towers_y[i], *this->tower_width, *this->tower_height);
        if (this->level=="level-1")
            this->towermanager->towers[i]->refreshRangeAB(this->core, this->core->conf->gl1->towerscenter[i]);
        else
            this->towermanager->towers[i]->refreshRangeAB(this->core, this->core->conf->gl2->towerscenter[i]);
    }
    if (this->selection>=0&&this->selection<*this->tower_cnt) {
        this->selection_x = -this->core->conf->ggame->selection_dx+this->towers_x[this->selection];
        this->selection_y = -this->core->conf->ggame->selection_dy+this->towers_y[this->selection];
        this->core->menumanager->buttonmanager->getGameSelection()->refresh(selection_x, selection_y, *selection_width, *selection_height);
    }
    if (this->isBTShowed) refreshBT(this->core);
    if (this->isUpgradeShowed) refreshUpgrade(this->core);
    if (this->isRemoveShowed) refreshRemove(this->core);
    if (this->isInSettlement) this->core->menumanager->buttonmanager->getGameWL()->refresh(this->core->conf->ggame->wl_x, this->core->conf->ggame->wl_y, this->core->conf->ggame->wl_width, this->core->conf->ggame->wl_height);
    this->enemymanager->refreshAllEnemies();
    this->bulletmanager->refreshAllBullets();
    this->refreshProgressBar();
    this->hiteffectmanager->refreshAllHitEffects();
    this->animationmanager->refreshAllCircularAnimations();
}
