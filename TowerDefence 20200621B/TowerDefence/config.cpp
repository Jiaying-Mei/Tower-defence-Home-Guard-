#include "config.h"
#include <QDebug>

View_Info::View_Info() {

}

void View_Info::build(double wratio, double hratio) {
    this->view_width = (int)(3000*wratio);
    this->view_height = (int)(2000*hratio);
}

GUI_MI::GUI_MI() {

}

void GUI_MI::build(double wratio, double hratio) {
    this->scene_width = (int)(3000*wratio);
    this->scene_height = (int)(2000*hratio);
    this->intro_x = (int)(1049*wratio);
    this->intro_y = (int)(500*hratio);
    this->intro_width = (int)(902*wratio);
    this->intro_height = (int)(200*hratio);
    this->start_x = (int)(1104*wratio);
    this->start_y = (int)(900*hratio);
    this->start_width = (int)(792*wratio);
    this->start_height = (int)(200*hratio);
    this->exit_x = (int)(1130*wratio);
    this->exit_y = (int)(1300*hratio);
    this->exit_width = (int)(740*wratio);
    this->exit_height = (int)(200*hratio);
}

GUI_BI::GUI_BI() {

}

void GUI_BI::build(double wratio, double hratio) {
    this->scene_width = (int)(3000*wratio);
    this->scene_height = (int)(2000*hratio);
    this->back_x = (int)(2700*wratio);
    this->back_y = (int)(1700*hratio);
    this->back_width = (int)(200*wratio);
    this->back_height = (int)(200*hratio);
}

GUI_LS::GUI_LS() {

}

void GUI_LS::build(double wratio, double hratio) {
    this->scene_width = (int)(3000*wratio);
    this->scene_height = (int)(2000*hratio);
    this->level_1_x = (int)(150*wratio);
    this->level_1_y = (int)(620*hratio);
    this->level_1_width = (int)(1300*wratio);
    this->level_1_height = (int)(1475*hratio);
    //非对称布局 = =
    this->level_2_x = (int)(1575*wratio);
    this->level_2_y = (int)(620*hratio);
    this->level_2_width = (int)(1300*wratio);
    this->level_2_height = (int)(1475*hratio);
    this->back_x = (int)(2700*wratio);
    this->back_y = (int)(1700*hratio);
    this->back_width = (int)(200*wratio);
    this->back_height = (int)(200*hratio);
}

GUI_Game::GUI_Game() {
    this->cp_y = 0;
    this->restart_y = 0;
    this->back_y = 0;
    this->coin_x = 0;
    this->coin_y = 0;
    this->health_x = 0;
    this->wl_y = 0;
    this->enemy_dw = 82;
    this->enemy_dh = 105;
}

void GUI_Game::build(double wratio, double hratio) {
    this->scene_width = (int)(3000*wratio);
    this->scene_height = (int)(2000*hratio);
    this->cp_x = (int)(2400*wratio);
    this->cp_width = (int)(200*wratio);
    this->cp_height = (int)(200*hratio);
    this->restart_x = (int)(2600*wratio);
    this->restart_width = (int)(200*wratio);
    this->restart_height = (int)(200*hratio);
    this->back_x = (int)(2800*wratio);
    this->back_width = (int)(200*wratio);
    this->back_height = (int)(200*hratio);
    this->selection_width = (int)(240*wratio);
    this->selection_height = (int)(240*hratio);
    this->selection_dx = (int)(20*wratio);
    this->selection_dy = (int)(20*hratio);
    this->coin_width = (int)(200*wratio);
    this->coin_height = (int)(200*hratio);
    this->health_y = (int)(200*hratio);
    this->health_width = (int)(200*wratio);
    this->health_height = (int)(200*hratio);
    this->log_x = (int)(400*wratio);
    this->log_y = (int)(1850*hratio);
    this->coinfont = (int)(60*hratio);
    this->healthfont = (int)(60*hratio);
    this->logfont = (int)(24*hratio);
    this->wl_width = (int)(2318*wratio);
    this->wl_height = (int)(2000*hratio);
    this->wl_x = (int)(341*wratio);
    this->bt1_width = (int)(300*wratio);
    this->bt1_height = (int)(180*hratio);
    this->bt1_x = (int)(20*wratio);
    this->bt1_y = (int)(500*hratio);
    this->bt2_width = (int)(300*wratio);
    this->bt2_height = (int)(180*hratio);
    this->bt2_x = (int)(20*wratio);
    this->bt2_y = (int)(700*hratio);
    this->bt3_width = (int)(300*wratio);
    this->bt3_height = (int)(180*hratio);
    this->bt3_x = (int)(20*wratio);
    this->bt3_y = (int)(900*hratio);
    this->upgrade_width = (int)(200*wratio);
    this->upgrade_height = (int)(200*hratio);
    this->upgrade_x = (int)(70*wratio);
    this->upgrade_y = (int)(1100*hratio);
    this->remove_width = (int)(200*wratio);
    this->remove_height = (int)(200*hratio);
    this->remove_x = (int)(70*wratio);
    this->remove_y = (int)(1300*hratio);
    this->enemy_width = (int)(165*wratio);
    this->enemy_height = (int)(210*hratio);
    this->enemyhealthbar_width = (int)(165*wratio);
    this->enemyhealthbar_height = (int)(24*hratio);
    this->bullet_width = (int)(80*wratio);
    this->bullet_height = (int)(80*hratio);
}

GUI_Level1::GUI_Level1() {
    this->initialcoin = 500;
    this->initialhealth = 10;
    this->tower_cnt = 6;
    this->towerscenter = (AcidPoint*)malloc(sizeof(AcidPoint)*6);
    this->towerscenter[0] = AcidPoint(2743, 531);
    this->towerscenter[1] = AcidPoint(1452, 518);
    this->towerscenter[2] = AcidPoint(1423, 1195);
    this->towerscenter[3] = AcidPoint(2292, 1707);
    this->towerscenter[4] = AcidPoint(2247, 1098);
    this->towerscenter[5] = AcidPoint(868, 1419);
    this->waves.push_back(Wave("Enemy1", 300, 0));
    this->waves.push_back(Wave("Enemy2", 400, 0));
    this->waves.push_back(Wave("Enemy1", 500, 0));
    this->waves.push_back(Wave("Enemy1", 800, 0));
    this->waves.push_back(Wave("Enemy1", 850, 0));
    this->waves.push_back(Wave("Enemy3", 900, 0));
}

void GUI_Level1::build(double wratio, double hratio) {
    this->tower_width = (int)(200*wratio);
    this->tower_height = (int)(200*hratio);
    this->tower_x[0] = (int)(2643*wratio);
    this->tower_x[1] = (int)(1352*wratio);
    this->tower_x[2] = (int)(1323*wratio);
    this->tower_x[3] = (int)(2192*wratio);
    this->tower_x[4] = (int)(2147*wratio);
    this->tower_x[5] = (int)(768*wratio);
    this->tower_y[0] = (int)(431*hratio);
    this->tower_y[1] = (int)(418*hratio);
    this->tower_y[2] = (int)(1095*hratio);
    this->tower_y[3] = (int)(1607*hratio);
    this->tower_y[4] = (int)(998*hratio);
    this->tower_y[5] = (int)(1319*hratio);
}

AcidPoint GUI_Level1::getPos(int route, int pos) {
    if (route==0) {
        if (pos<=600) return AcidPoint(3000-pos, 1360);
        if (pos<=1260) return AcidPoint(2400, 1960-pos);
        if (pos<=2075) return AcidPoint(3660-pos, 700);
        if (pos<=2735) return AcidPoint(1585,pos-1375);
        if (pos<=3290) return AcidPoint(4320-pos, 1360);
        if (pos<=3620) return AcidPoint(1030, 4650-pos);
        if (pos<=4450) return AcidPoint(4650-pos, 1030);
    }
    return AcidPoint(-1, -1);
}

GUI_Level2::GUI_Level2() {
    this->initialcoin = 300;
    this->initialhealth = 5;
    this->tower_cnt = 4;
    this->towerscenter = (AcidPoint*)malloc(sizeof(AcidPoint)*4);
    this->towerscenter[0] = AcidPoint(2252, 1152);
    this->towerscenter[1] = AcidPoint(1474, 1128);
    this->towerscenter[2] = AcidPoint(684, 465);
    this->towerscenter[3] = AcidPoint(910, 1695);
    this->waves.push_back(Wave("Enemy1", 200, 1));
    this->waves.push_back(Wave("Enemy2", 300, 0));
    this->waves.push_back(Wave("Enemy3", 400, 0));
    this->waves.push_back(Wave("Enemy1", 500, 0));
    this->waves.push_back(Wave("Enemy1", 600, 0));
    this->waves.push_back(Wave("Enemy1", 700, 0));
    this->waves.push_back(Wave("Enemy3", 800, 0));
    this->waves.push_back(Wave("Enemy3", 850, 0));
}

void GUI_Level2::build(double wratio, double hratio) {
    this->tower_width = (int)(200*wratio);
    this->tower_height = (int)(200*hratio);
    this->tower_x[0] = (int)(2152*wratio);
    this->tower_x[1] = (int)(1374*wratio);
    this->tower_x[2] = (int)(584*wratio);
    this->tower_x[3] = (int)(810*wratio);
    this->tower_y[0] = (int)(1052*hratio);
    this->tower_y[1] = (int)(1028*hratio);
    this->tower_y[2] = (int)(365*hratio);
    this->tower_y[3] = (int)(1595*hratio);
}

AcidPoint GUI_Level2::getPos(int route, int pos) {
    if (route==0) {
        if (pos<=570) return AcidPoint(3000-pos, 675);
        if (pos<=1205) return AcidPoint(2430, pos+105);
        if (pos<=2005) return AcidPoint(3635-pos, 1310);
        if (pos<=2640) return AcidPoint(1630, 3315-pos);
        if (pos<=3440) return AcidPoint(4270-pos, 675);
        if (pos<=4075) return AcidPoint(830, pos-2765);
        if (pos<=4705) return AcidPoint(4905-pos, 1310);
    } else if (route==1) {
        if (pos<=570) return AcidPoint(3000-pos, 675);
        if (pos<=1205) return AcidPoint(2430, pos+105);
        if (pos<=3435) return AcidPoint(3635-pos, 1310);
    }
    return AcidPoint(-1, -1);
}

Towers_Info::Towers_Info() {
    this->tower1 = new Tower_Data;
    this->tower1->towername = "Tower1";
    this->tower1->maxlevel = 2;
    this->tower1->upgradecost.push_back(50);
    this->tower1->demolitionfeedback.push_back(20);
    this->tower1->cooldown.push_back(100);
    this->tower1->bullet.push_back("bullet11");
//this->tower1->damage.push_back(10);
    this->tower1->info.push_back("Primary Mushroom  Upgrade: 25 Return: 20 Damage: 10 CD: 1s");
    this->tower1->imageurl.push_back(":/image/tower11.png");
    this->tower1->upgradecost.push_back(25);
    this->tower1->demolitionfeedback.push_back(30);
    this->tower1->cooldown.push_back(200);
    this->tower1->bullet.push_back("bullet12");
//this->tower1->damage.push_back(15);
    this->tower1->info.push_back("Premium Mushroom!  Return: 30 Damage: 15 CD: 2s");
    this->tower1->imageurl.push_back(":/image/tower12.png");

    this->tower2 = new Tower_Data;
    this->tower2->towername = "Tower2";
    this->tower2->maxlevel = 1;
    this->tower2->upgradecost.push_back(100);
    this->tower2->demolitionfeedback.push_back(80);
    this->tower2->cooldown.push_back(500);
    this->tower2->bullet.push_back("bullet21");
//this->tower2->damage.push_back(75);
    this->tower2->info.push_back("Sunflower Return: 80 Damage: 75 CD: 5s");
    this->tower2->imageurl.push_back(":/image/tower21.png");

    this->tower3 = new Tower_Data;
    this->tower3->towername = "Tower3";
    this->tower3->maxlevel = 3;
    this->tower3->upgradecost.push_back(50);
    this->tower3->demolitionfeedback.push_back(40);
    this->tower3->cooldown.push_back(100);
    this->tower3->bullet.push_back("bullet31");
//this->tower3->damage.push_back(25);
    this->tower3->info.push_back("Primary PeaShooter  Upgrade: 25 Return: 40 Damage: 25 CD: 1s");
    this->tower3->imageurl.push_back(":/image/tower31.png");
    this->tower3->upgradecost.push_back(25);
    this->tower3->demolitionfeedback.push_back(50);
    this->tower3->cooldown.push_back(200);
    this->tower3->bullet.push_back("bullet32");
//this->tower3->damage.push_back(50);
    this->tower3->info.push_back("Medium PeaShooter  Upgrade：25 Return: 50 Damage: 50 CD: 2s");
    this->tower3->imageurl.push_back(":/image/tower32.png");
    this->tower3->upgradecost.push_back(25);
    this->tower3->demolitionfeedback.push_back(75);
    this->tower3->cooldown.push_back(500);
    this->tower3->bullet.push_back("bullet33");
//this->tower3->damage.push_back(75);
    this->tower3->info.push_back("Premium PeaShooter!  Return: 75 Damage: 75 CD: 5s");
    this->tower3->imageurl.push_back(":/image/tower33.png");
}

Tower_Data* Towers_Info::getTower(string targettowername) {
    if (targettowername == "Tower1")
        return this->tower1;
    if (targettowername == "Tower2")
        return this->tower2;
    if (targettowername == "Tower3")
        return this->tower3;
    return NULL;
}

Enemies_Info::Enemies_Info() {
    this->enemy1 = new Enemy_Data;
    enemy1->enemyname = "Enemy1";
    enemy1->imageurl = ":/image/enemy1.gif";
    enemy1->health = 100;
    enemy1->speed = 3;
    enemy1->damage = 1;
    enemy1->reward = 20;
    this->enemy2 = new Enemy_Data;
    enemy2->enemyname = "Enemy2";
    enemy2->imageurl = ":/image/enemy2.gif";
    enemy2->health = 250;
    enemy2->speed = 2;
    enemy2->damage = 2;
    enemy2->reward = 50;
    this->enemy3 = new Enemy_Data;
    enemy3->enemyname = "Enemy3";
    enemy3->imageurl = ":/image/enemy3.gif";
    enemy3->health = 200;
    enemy3->speed = 4;
    enemy3->damage = 5;
    enemy3->reward = 100;
}

Enemy_Data* Enemies_Info::getEnemy(string targetenemyname) {
    if (targetenemyname == "Enemy1")
        return this->enemy1;
    if (targetenemyname == "Enemy2")
        return this->enemy2;
    if (targetenemyname == "Enemy3")
        return this->enemy3;
    return NULL;
}

int Bullet_Data::getRange() {
    return this->speed*this->duration;
}

Bullets_Info::Bullets_Info() {
    this->bullet11 = new Bullet_Data;
    this->bullet11->speed = 15;
    this->bullet11->damage = 10;
    this->bullet11->duration = 50;
    this->bullet11->imageurl = ":/image/bullet11.gif";
    this->bullet11->hiteffect = "hiteffect11";
    this->bullet11->bulletname = "bullet11";
    this->bullet11->frozenduration = 0;
    this->bullet11->hitdistance = 80;
    this->bullet12 = new Bullet_Data;
    this->bullet12->speed = 20;
    this->bullet12->damage = 15;
    this->bullet12->duration = 50;
    this->bullet12->imageurl = ":/image/bullet12.gif";
    this->bullet12->hiteffect = "hiteffect12";
    this->bullet12->bulletname = "bullet12";
    this->bullet12->frozenduration = 0;
    this->bullet12->hitdistance = 80;

    this->bullet21 = new Bullet_Data;
    this->bullet21->speed = 1;
    this->bullet21->damage = 75;
    this->bullet21->duration = 5;
    this->bullet21->imageurl = ":/image/bullet21.png";
    this->bullet21->hiteffect = "hiteffect21";
    this->bullet21->bulletname = "bullet21";
    this->bullet21->frozenduration = 0;
    this->bullet21->hitdistance = 80;

    this->bullet31 = new Bullet_Data;
    this->bullet31->speed = 15;
    this->bullet31->damage = 25;
    this->bullet31->duration = 50;
    this->bullet31->imageurl = ":/image/bullet31.gif";
    this->bullet31->hiteffect = "hiteffect31";
    this->bullet31->bulletname = "bullet31";
    this->bullet31->frozenduration = 0;
    this->bullet31->hitdistance = 80;
    this->bullet32 = new Bullet_Data;
    this->bullet32->speed = 20;
    this->bullet32->damage = 50;
    this->bullet32->duration = 50;
    this->bullet32->imageurl = ":/image/bullet32.gif";
    this->bullet32->hiteffect = "hiteffect32";
    this->bullet32->bulletname = "bullet32";
    this->bullet32->frozenduration = 0;
    this->bullet32->hitdistance = 80;
    this->bullet33 = new Bullet_Data;
    this->bullet33->speed = 30;
    this->bullet33->damage = 75;
    this->bullet33->duration = 50;
    this->bullet33->imageurl = ":/image/bullet33.gif";
    this->bullet33->hiteffect = "hiteffect33";
    this->bullet33->bulletname = "bullet33";
    this->bullet33->frozenduration = 500;
    this->bullet33->hitdistance = 80;
}

Bullet_Data* Bullets_Info::getBullet(string targetbulletname) {
    if (targetbulletname=="bullet11")
        return this->bullet11;
    if (targetbulletname=="bullet12")
        return this->bullet12;
    if (targetbulletname=="bullet21")
        return this->bullet21;
    if (targetbulletname=="bullet31")
        return this->bullet31;
    if (targetbulletname=="bullet32")
        return this->bullet32;
    if (targetbulletname=="bullet33")
        return this->bullet33;
    return NULL;
}

Config::Config() {
    this->vi = new View_Info;
    this->gmi = new GUI_MI;
    this->gbi = new GUI_BI;
    this->gls = new GUI_LS;
    this->ggame = new GUI_Game;
    this->gl1 = new GUI_Level1;
    this->gl2 = new GUI_Level2;
    this->tsi = new Towers_Info;
    this->esi = new Enemies_Info;
    this->bsi = new Bullets_Info;
}

void Config::setCore(Core *aCore) {
    this->core=aCore;
}

void Config::build() {
    double targetwratio = this->nowwratio;
    double targethratio = this->nowhratio;
    this->vi->build(targetwratio, targethratio);
    this->gmi->build(targetwratio, targethratio);
    this->gbi->build(targetwratio, targethratio);
    this->gls->build(targetwratio, targethratio);
    this->ggame->build(targetwratio, targethratio);
    this->gl1->build(targetwratio, targethratio);
    this->gl2->build(targetwratio, targethratio);
}
