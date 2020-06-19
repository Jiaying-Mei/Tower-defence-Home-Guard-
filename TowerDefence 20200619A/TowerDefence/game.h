#ifndef GAME_H
#define GAME_H
#include "menu.h"
#include "config.h"
#include <string>
#include <vector>
#include <queue>
#include <QGraphicsRectItem>
using namespace std;

class Core;

class Tower:public AcidButton {
private:
    string type, bulletname;
    int level, cooldown, damage;
public:
    Tower(string tname, string tpath, QGraphicsScene *tscene, int pos_x, int pos_y, int ABwidth, int ABheight):AcidButton(tname, tpath, tscene, pos_x, pos_y, ABwidth, ABheight) {
        this->getItem()->setZValue(1);
        this->type = "None";
        this->level = 0;
        this->cooldown = 99999999;
        this->damage = 0;
    }
    string getType();
    int getLevel();
    int getRange(Core *aCore);
    void setTower(string towertype, string towerimageurl, int towerlevel, int towercooldown, string towerbulletname);
};

class TowerManager {
private:
    Core *core;
public:
    vector<Tower*> towers;
    void setCore(Core *aCore);
    void clear();
};

class Enemy:public AcidButton {
private:
    string type;
    int HP, speed, route, pos, frozen, reward, damage;
public:
    Enemy(string tname, int tHP, int tspeed, int troute, int treward, int tdamage, string tpath, QGraphicsScene *tscene, int pos_x, int pos_y, int ABwidth, int ABheight):AcidButton(tname, tpath, tscene, pos_x, pos_y, ABwidth, ABheight) {
        this->getItem()->setZValue(1);
        this->type = tname;
        this->HP = tHP;
        this->speed = tspeed;
        this->route = troute;
        this->reward = treward;
        this->damage = tdamage;
        this->pos = 0;
        this->frozen = 0;
    }
    void setRoute(int troute);
    void move();
    bool takeHP(int tdamage);
    void addFrozenDuration(int tDuration);
    bool isDied();
    int getReward();
    int getDamage();
    bool refreshE(Core *aCore);
    void remove(Core *aCore);
};

class EnemyManager {
private:
    Core *core;
    vector<Enemy*> enemies;
public:
    void setCore(Core *aCore);
    Enemy* getEnemy1();
    Enemy* getEnemy2();
    Enemy* getEnemy3();
    Enemy* getEnemy(string enemytype);
    void removeAllEnemies();
    void addEnemy(string enemytype, int route);
    void checkHP();
    void run();
    void refreshAllEnemies();
};

class Bullet:public AcidButton {
private:
    string type, hiteffectname;
    AcidPoint *fpos, *tpos;
    int speed, ntick, mtick, damage, frozen;
public:
    Bullet(Bullet_Data* tbd, string tname, string tpath, QGraphicsScene *tscene, int pos_x, int pos_y, int ABwidth, int ABheight):AcidButton(tname, tpath, tscene, pos_x, pos_y, ABwidth, ABheight) {
        this->getItem()->setZValue(1);
        this->type = tbd->bulletname;
        this->hiteffectname = tbd->hiteffect;
        this->speed = tbd->speed;
        this->ntick = 0;
        this->mtick = tbd->duration;
        this->damage = tbd->damage;
        this->frozen = 0;
        this->fpos = (AcidPoint*)malloc(sizeof(AcidPoint));
        this->tpos = (AcidPoint*)malloc(sizeof(AcidPoint));
    }
};

class BulletManager {
private:
    Core *core;
    vector<Bullet*> bullets;
public:
    void setCore(Core *aCore);
};

class AnimationManager {
private:
    Core *core;
    bool isRunning;
    QTimer *GameTimer;
public:
    AnimationManager(Core *aCore);
    void start();
    void stop();
};

class GameManager {
private:
    Core *core;
    string level;
    bool isPaused, isLoading, isInSettlement, isBTShowed, isUpgradeShowed, isRemoveShowed;
    int coin, health, selection;
    int *initialcoin, *initialhealth, *tower_cnt, *tower_width, *tower_height, *towers_x, *towers_y, *selection_width, *selection_height, selection_x, selection_y;
    void loadLevel1();
    void loadLevel2();
public:
    GameManager();
    TowerManager *towermanager;
    EnemyManager *enemymanager;
    AnimationManager *animationmanager;
    int tick;
    queue<Wave> qw;
    void setCore(Core *aCore);
    void loadLevel(string levelname);
    void toggleCP();
    void reloadLevel();
    void setCoin(int c);
    bool hasCoin(int c);
    void giveCoin(int c);
    void takeCoin(int c);
    int getCoin();
    void setHealth(int h);
    bool hasHealth(int h);
    void giveHealth(int h);
    void takeHealth(int h);
    int getHealth();
    void setSelection(int targetSelection);
    void initSelection();
    int getSelection();
    int getTowerID(QGraphicsItem *citem);
    void showSelection();
    void hideSelection();
    void showSettlement(string result);
    void hideSettlement();
    bool getIsInSettlement();
    void showBT();
    void hideBT();
    bool getIsBTShowed();
    void showUpgrade();
    void hideUpgrade();
    bool getIsUpgradeShowed();
    void showRemove();
    void hideRemove();
    bool getIsRemoveShowed();
    AcidPoint getPos(int troute, int tpos);
    void refresh();
};

#endif // GAME_H
