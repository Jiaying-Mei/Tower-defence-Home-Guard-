#ifndef CONFIG_H
#define CONFIG_H
#include <string>
#include <vector>
using namespace std;

class Core;

class View_Info {
public:
    View_Info();
    void build(double wratio, double hratio);
    int view_width, view_height;
};

class GUI_MI {
public:
    GUI_MI();
    void build(double wratio, double hratio);
    int scene_width, scene_height;
    int intro_width, intro_height, intro_x, intro_y;
    int start_width, start_height, start_x, start_y;
    int exit_width, exit_height, exit_x, exit_y;
};

class GUI_BI {
public:
    GUI_BI();
    void build(double wratio, double hratio);
    int scene_width, scene_height;
    int back_width, back_height, back_x, back_y;
};

class GUI_LS {
public:
    GUI_LS();
    void build(double wratio, double hratio);
    int scene_width, scene_height;
    int level_1_width, level_1_height, level_1_x, level_1_y;
    int level_2_width, level_2_height, level_2_x, level_2_y;
    int back_width, back_height, back_x, back_y;
};

class GUI_Game {
public:
    GUI_Game();
    void build(double wratio, double hratio);
    int scene_width, scene_height;
    int cp_width, cp_height, cp_x, cp_y;
    int restart_width, restart_height, restart_x, restart_y;
    int back_width, back_height, back_x, back_y;
    int selection_width, selection_height, selection_dx, selection_dy;
    int coin_width, coin_height, coin_x, coin_y;
    int health_width, health_height, health_x, health_y;
    int log_x, log_y;
    int coinfont, healthfont, logfont;
    int wl_width, wl_height, wl_x, wl_y;
    int bt1_width, bt1_height, bt1_x, bt1_y;
    int bt2_width, bt2_height, bt2_x, bt2_y;
    int bt3_width, bt3_height, bt3_x, bt3_y;
    int upgrade_width, upgrade_height, upgrade_x, upgrade_y;
    int remove_width, remove_height, remove_x, remove_y;
    int enemy_width, enemy_height, enemy_dw, enemy_dh;
    int enemyhealthbar_width, enemyhealthbar_height;
    int bullet_width, bullet_height;
};

struct Wave {
    string enemytype;
    int time, route;
    Wave(string tet, int tt,  int tr) {
        this->enemytype = tet;
        this->time = tt;
        this->route = tr;
    }
};

struct AcidPoint {
    int x, y;
    AcidPoint(int tx, int ty) {
        this->x = tx;
        this->y = ty;
    }
};

class GUI_Level1 {
public:
    GUI_Level1();
    void build(double wratio, double hratio);
    int initialcoin, initialhealth, tower_cnt;
    int tower_width, tower_height, tower_x[6], tower_y[6];
    vector<Wave> waves;
    AcidPoint getPos(int route, int pos);
    AcidPoint *towerscenter;
};

class GUI_Level2 {
public:
    GUI_Level2();
    void build(double wratio, double hratio);
    int initialcoin, initialhealth, tower_cnt;
    int tower_width, tower_height, tower_x[4], tower_y[4];
    vector<Wave> waves;
    AcidPoint getPos(int route, int pos);
    AcidPoint *towerscenter;
};

class Tower_Data {
public:
    string towername;
    int maxlevel;
    vector<int> upgradecost, demolitionfeedback, cooldown;
    vector<string> info, imageurl, bullet;
};

class Towers_Info {
public:
    Towers_Info();
    Tower_Data *tower1, *tower2, *tower3;
    Tower_Data* getTower(string targettowername);
};

class Enemy_Data {
public:
    string enemyname, imageurl;
    int health, speed, damage, reward;
};

class Enemies_Info {
public:
    Enemies_Info();
    Enemy_Data *enemy1, *enemy2, *enemy3;
    Enemy_Data* getEnemy(string targetenemyname);
};

class Bullet_Data {
public:
    string bulletname, imageurl, hiteffect;
    int speed, duration, damage, frozenduration, hitdistance;
    int getRange();
};

class Bullets_Info {
public:
    Bullets_Info();
    Bullet_Data *bullet11, *bullet12, *bullet21, *bullet31, *bullet32, *bullet33;
    Bullet_Data* getBullet(string targetbulletname);
};

class Config {
private:
    Core *core;
public:
    double nowwratio=1.0, nowhratio=1.0;
    //double nowwratio=0.5, nowhratio=0.5;
    Config();
    void setCore(Core *aCore);
    void build();
    View_Info *vi;
    GUI_MI *gmi;
    GUI_BI *gbi;
    GUI_LS *gls;
    GUI_Game *ggame;
    GUI_Level1 *gl1;
    GUI_Level2 *gl2;
    Towers_Info *tsi;
    Enemies_Info *esi;
    Bullets_Info *bsi;
};

#endif // CONFIG_H
