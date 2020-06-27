#include "menu.h"
#include "config.h"
#include "audio.h"
#include "game.h"
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QIcon>
#include <QPixmap>
#include <map>
#include <string>
#include <sstream>
using namespace std;
#include <QDebug>

//unused
QGraphicsRectItem* createAcidButton(string path, int ABwidth, int ABheight) {
    QGraphicsRectItem* item = new QGraphicsRectItem(0,0,ABwidth,ABheight);
    item->setPen(QPen(Qt::transparent));
    item->setBrush(QPixmap(path.c_str()).scaled(QSize(ABwidth,ABheight)));
    return item;
}

MenuView::MenuView(QWidget *parent):
    QGraphicsView(parent)
{

}

void MenuView::setCore(Core *aCore) {
    this->core = aCore;
}

void MenuView::mousePressEvent(QMouseEvent *event) {
    QPoint viewPos = event->pos();
    QPointF scenePos = mapToScene(viewPos);
    QGraphicsItem *item= scene()->itemAt(scenePos,QTransform());
    if (item) {
        if (scene()->objectName()=="MainInterfaceScene")
            this->core->menumanager->buttonmanager->clickMainInterface(this->core, item);
        if (scene()->objectName()=="IntroductionScene")
            this->core->menumanager->buttonmanager->clickIntroduction(this->core, item);
        if (scene()->objectName()=="LevelSelectionScene")
            this->core->menumanager->buttonmanager->clickLevelSelection(this->core, item);
        if (scene()->objectName()=="GameScene")
            this->core->menumanager->buttonmanager->clickGame(this->core, item);
    }
}

void virtualClick(Core *aCore, int key) {
    if (key==1 && aCore->gamemanager->getIsBTShowed())
        aCore->menumanager->buttonmanager->clickGame(aCore, aCore->menumanager->buttonmanager->getGameBT1()->getItem());
    if (key==2 && aCore->gamemanager->getIsBTShowed())
        aCore->menumanager->buttonmanager->clickGame(aCore, aCore->menumanager->buttonmanager->getGameBT2()->getItem());
    if (key==3 && aCore->gamemanager->getIsBTShowed())
        aCore->menumanager->buttonmanager->clickGame(aCore, aCore->menumanager->buttonmanager->getGameBT3()->getItem());
    if (key==4 && aCore->gamemanager->getIsUpgradeShowed())
        aCore->menumanager->buttonmanager->clickGame(aCore, aCore->menumanager->buttonmanager->getGameUpgrade()->getItem());
    if (key==5 && aCore->gamemanager->getIsRemoveShowed())
        aCore->menumanager->buttonmanager->clickGame(aCore, aCore->menumanager->buttonmanager->getGameRemove()->getItem());
}

void MenuView::keyPressEvent(QKeyEvent *event) {
    if (!this->core->inited) return;
    if (this->scene()->objectName()=="GameScene") {
        if (event->key() == Qt::Key_1) virtualClick(this->core, 1);
        if (event->key() == Qt::Key_2) virtualClick(this->core, 2);
        if (event->key() == Qt::Key_3) virtualClick(this->core, 3);
        if (event->key() == Qt::Key_4) virtualClick(this->core, 4);
        if (event->key() == Qt::Key_5) virtualClick(this->core, 5);
        if (!this->core->debug) return;
        if (event->key() == Qt::Key_Q) this->core->gamemanager->giveCoin(1000);
        if (event->key() == Qt::Key_W) this->core->gamemanager->enemymanager->removeAllEnemies();
        if (event->key() == Qt::Key_E) this->core->gamemanager->bulletmanager->removeAllBullets();

        if (event->key() == Qt::Key_J) this->core->gamemanager->enemymanager->addEnemy("Enemy1", 0);
        if (event->key() == Qt::Key_K) this->core->gamemanager->enemymanager->addEnemy("Enemy2", 0);
        if (event->key() == Qt::Key_L) this->core->gamemanager->enemymanager->addEnemy("Enemy3", 0);

        //if (event->key() == Qt::Key_T) this->core->gamemanager->enemymanager->addEnemy("Enemy1", 0);
        //if (event->key() == Qt::Key_R) this->core->gamemanager->enemymanager->removeAllEnemies();
        //if (event->key() == Qt::Key_C) this->core->gamemanager->enemymanager->checkHP();
        //if (event->key() == Qt::Key_P) this->core->gamemanager->bulletmanager->addBullet11("bullet31", 0, AcidPoint(1,1));
    }
}

void MenuView::resizeEvent(QResizeEvent  *event) {
    this->core->resize(event->size().width(), event->size().height());
}

AcidButton::AcidButton(string tname, string tpath, QGraphicsScene *tscene, int pos_x, int pos_y, int ABwidth, int ABheight) {
    this->bname = tname;
    this->bimage = QPixmap(tpath.c_str());
    this->bitem = new QGraphicsRectItem(0,0,ABwidth,ABheight);
    this->bitem->setPen(QPen(Qt::transparent));
    this->bitem->setBrush(this->bimage.scaled(QSize(ABwidth,ABheight)));
    tscene->addItem(this->bitem);
    this->bitem->setPos(pos_x, pos_y);
}

bool AcidButton::isEqual(QGraphicsItem *oitem)  {
    return this->bitem->pos()==oitem->pos();
}

void AcidButton::refresh(int pos_x, int pos_y, int ABwidth, int ABheight) {
    this->bitem->setRect(0, 0, ABwidth, ABheight);
    this->bitem->setBrush(this->bimage.scaled(QSize(ABwidth,ABheight)));
    this->bitem->setPos(pos_x, pos_y);
}

void AcidButton::setPixmap(string tpath) {
    this->bimage = QPixmap(tpath.c_str());
    this->bitem->setBrush(this->bimage.scaled(QSize(this->bitem->rect().width(), this->bitem->rect().height())));
}

QGraphicsRectItem* AcidButton::getItem() {
    return this->bitem;
}

ButtonManager::ButtonManager(Core *aCore) {
    //Main Interface Buttons
    this->mi_bg = new AcidButton("mi bg", aCore->pathprefix + "image/main interface.jpg", &aCore->menumanager->MainInterfaceScene,0, 0, aCore->conf->gmi->scene_width, aCore->conf->gmi->scene_height);
    this->mi_intro = new AcidButton("mi intro", aCore->pathprefix + "image/intro icon.png", &aCore->menumanager->MainInterfaceScene, aCore->conf->gmi->intro_x, aCore->conf->gmi->intro_y, aCore->conf->gmi->intro_width, aCore->conf->gmi->intro_height);
    this->mi_start = new AcidButton("mi start", aCore->pathprefix + "image/start icon.png", &aCore->menumanager->MainInterfaceScene, aCore->conf->gmi->start_x, aCore->conf->gmi->start_y, aCore->conf->gmi->start_width, aCore->conf->gmi->start_height);
    this->mi_exit = new AcidButton("mi exit", aCore->pathprefix + "image/exit icon.png", &aCore->menumanager->MainInterfaceScene, aCore->conf->gmi->exit_x, aCore->conf->gmi->exit_y, aCore->conf->gmi->exit_width, aCore->conf->gmi->exit_height);
    this->mi_debug = new AcidButton("mi debug", aCore->pathprefix + "image/debug F.png", &aCore->menumanager->MainInterfaceScene, aCore->conf->gmi->debug_x, aCore->conf->gmi->debug_y, aCore->conf->gmi->debug_width, aCore->conf->gmi->debug_height);
    //Introduction Buttons
    this->bi_bg = new AcidButton("bi bg", aCore->pathprefix + "image/introduction.png", &aCore->menumanager->IntroductionScene, 0, 0, aCore->conf->gbi->scene_width, aCore->conf->gbi->scene_height);
    this->bi_back = new AcidButton("bi back", aCore->pathprefix + "image/back icon.png", &aCore->menumanager->IntroductionScene, aCore->conf->gbi->back_x, aCore->conf->gbi->back_y, aCore->conf->gbi->back_width, aCore->conf->gbi->back_height);
    //Level Selection Buttons
    this->ls_bg = new AcidButton("ls bg", aCore->pathprefix + "image/level selection.png", &aCore->menumanager->LevelSelectionScene, 0, 0, aCore->conf->gls->scene_width, aCore->conf->gls->scene_height);
    this->ls_level_1 = new AcidButton("ls level_1", aCore->pathprefix + "image/level_1 icon.png", &aCore->menumanager->LevelSelectionScene, aCore->conf->gls->level_1_x, aCore->conf->gls->level_1_y, aCore->conf->gls->level_1_width, aCore->conf->gls->level_1_height);
    this->ls_level_2 = new AcidButton("ls level_2", aCore->pathprefix + "image/level_2 icon.png", &aCore->menumanager->LevelSelectionScene, aCore->conf->gls->level_2_x, aCore->conf->gls->level_2_y, aCore->conf->gls->level_2_width, aCore->conf->gls->level_2_height);
    this->ls_back = new AcidButton("ls back", aCore->pathprefix + "image/back icon.png", &aCore->menumanager->LevelSelectionScene, aCore->conf->gls->back_x, aCore->conf->gls->back_y, aCore->conf->gls->back_width, aCore->conf->gls->back_height);
    this->ls_lock = new AcidButton("ls lock", aCore->pathprefix + "image/lock.png", &aCore->menumanager->LevelSelectionScene, aCore->conf->gls->lock_x, aCore->conf->gls->lock_y, aCore->conf->gls->lock_width, aCore->conf->gls->lock_height);
    if (!aCore->lock)
        aCore->menumanager->LevelSelectionScene.removeItem(this->ls_back->getItem());
    //Game Buttons
    this->game_bg = new AcidButton("game bg", aCore->pathprefix + "image/level1map.jpg", &aCore->menumanager->GameScene, 0, 0, aCore->conf->ggame->scene_width, aCore->conf->ggame->scene_height);
    this->game_cp = new AcidButton("game cp", aCore->pathprefix + "image/continue icon.png", &aCore->menumanager->GameScene, aCore->conf->ggame->cp_x, aCore->conf->ggame->cp_y, aCore->conf->ggame->cp_width, aCore->conf->ggame->cp_height);
    this->game_restart = new AcidButton("game restart", aCore->pathprefix + "image/restart icon.png", &aCore->menumanager->GameScene, aCore->conf->ggame->restart_x, aCore->conf->ggame->restart_y, aCore->conf->ggame->restart_width, aCore->conf->ggame->restart_height);
    this->game_back = new AcidButton("game back", aCore->pathprefix + "image/back icon.png", &aCore->menumanager->GameScene, aCore->conf->ggame->back_x, aCore->conf->ggame->back_y, aCore->conf->ggame->back_width, aCore->conf->ggame->back_height);
    this->game_selection = new AcidButton("game selection", aCore->pathprefix + "image/towerpositionselected.png", &aCore->menumanager->GameScene, 1, 1, aCore->conf->ggame->selection_width, aCore->conf->ggame->selection_height);
    aCore->menumanager->GameScene.removeItem(this->game_selection->getItem());
    this->game_coin = new AcidButton("game coin", aCore->pathprefix + "image/coin icon.png", &aCore->menumanager->GameScene, aCore->conf->ggame->coin_x, aCore->conf->ggame->coin_y, aCore->conf->ggame->coin_width, aCore->conf->ggame->coin_height);
    this->game_health = new AcidButton("game health", aCore->pathprefix + "image/health icon.png", &aCore->menumanager->GameScene, aCore->conf->ggame->health_x, aCore->conf->ggame->health_y, aCore->conf->ggame->health_width, aCore->conf->ggame->health_height);
    this->game_wl = new AcidButton("game wl", aCore->pathprefix + "image/win.png", &aCore->menumanager->GameScene, aCore->conf->ggame->wl_x, aCore->conf->ggame->wl_y, aCore->conf->ggame->wl_width, aCore->conf->ggame->wl_height);
    this->game_wl->getItem()->setZValue(3);
    aCore->menumanager->GameScene.removeItem(this->game_wl->getItem());
    this->game_bt1 = new AcidButton("game bt1", aCore->pathprefix + "image/build tower1.png", &aCore->menumanager->GameScene, aCore->conf->ggame->bt1_x, aCore->conf->ggame->bt1_y, aCore->conf->ggame->bt1_width, aCore->conf->ggame->bt1_height);
    aCore->menumanager->GameScene.removeItem(this->game_bt1->getItem());
    this->game_bt2 = new AcidButton("game bt2", aCore->pathprefix + "image/build tower2.png", &aCore->menumanager->GameScene, aCore->conf->ggame->bt2_x, aCore->conf->ggame->bt2_y, aCore->conf->ggame->bt2_width, aCore->conf->ggame->bt2_height);
    aCore->menumanager->GameScene.removeItem(this->game_bt2->getItem());
    this->game_bt3 = new AcidButton("game bt3", aCore->pathprefix + "image/build tower3.png", &aCore->menumanager->GameScene, aCore->conf->ggame->bt3_x, aCore->conf->ggame->bt3_y, aCore->conf->ggame->bt3_width, aCore->conf->ggame->bt3_height);
    aCore->menumanager->GameScene.removeItem(this->game_bt3->getItem());
    this->game_upgrade = new AcidButton("game upgrade", aCore->pathprefix + "image/upgrade tower.png", &aCore->menumanager->GameScene, aCore->conf->ggame->upgrade_x, aCore->conf->ggame->upgrade_y, aCore->conf->ggame->upgrade_width, aCore->conf->ggame->upgrade_height);
    aCore->menumanager->GameScene.removeItem(this->game_upgrade->getItem());
    this->game_remove = new AcidButton("game remove", aCore->pathprefix + "image/remove tower.png", &aCore->menumanager->GameScene, aCore->conf->ggame->remove_x, aCore->conf->ggame->remove_y, aCore->conf->ggame->remove_width, aCore->conf->ggame->remove_height);
    aCore->menumanager->GameScene.removeItem(this->game_remove->getItem());
    this->game_progressbar1 = new AcidButton("game pb1", aCore->pathprefix + "image/progress bar 1.png", &aCore->menumanager->GameScene, aCore->conf->ggame->progressbar_x, aCore->conf->ggame->progressbar_y, aCore->conf->ggame->progressbar_width, aCore->conf->ggame->progressbar_height);
    this->game_progressbar2 = new AcidButton("game pb2", aCore->pathprefix + "image/progress bar 2.png", &aCore->menumanager->GameScene, aCore->conf->ggame->progressbarinside_x, aCore->conf->ggame->progressbarinside_y, aCore->conf->ggame->progressbarinside_width, aCore->conf->ggame->progressbarinside_height);
    this->game_progressbar3 = new AcidButton("game pb3", aCore->pathprefix + "image/progress bar 3.png", &aCore->menumanager->GameScene, aCore->conf->ggame->progressbar_x, aCore->conf->ggame->progressbar_y, aCore->conf->ggame->progressbar_width, aCore->conf->ggame->progressbar_height);
    this->game_progressbar4 = new AcidButton("game pb4", aCore->pathprefix + "image/progress bar 4.png", &aCore->menumanager->GameScene, aCore->conf->ggame->progressbarhead_x, aCore->conf->ggame->progressbarhead_y, aCore->conf->ggame->progressbarhead_width, aCore->conf->ggame->progressbarhead_height);
    //Game Texts
    aCore->menumanager->game_cointext = aCore->menumanager->GameScene.addText("500");
    aCore->menumanager->game_cointext->setDefaultTextColor(QColor(Qt::yellow));
    aCore->menumanager->game_cointext->setPos(aCore->conf->ggame->coin_x+aCore->conf->ggame->coin_width, aCore->conf->ggame->coin_y);
    aCore->menumanager->game_cointext->setFont(QFont("Courier New" , aCore->conf->ggame->coinfont, QFont::Bold));
    aCore->menumanager->game_healthtext = aCore->menumanager->GameScene.addText("10");
    aCore->menumanager->game_healthtext->setDefaultTextColor(QColor(Qt::red));
    aCore->menumanager->game_healthtext->setPos(aCore->conf->ggame->health_x+aCore->conf->ggame->health_width, aCore->conf->ggame->health_y);
    aCore->menumanager->game_healthtext->setFont(QFont("Courier New" , aCore->conf->ggame->healthfont, QFont::Bold));
    aCore->menumanager->game_log = aCore->menumanager->GameScene.addText("Text Message");
    aCore->menumanager->game_log->setDefaultTextColor(QColor(Qt::white));
    aCore->menumanager->game_log->setPos(aCore->conf->ggame->log_x, aCore->conf->ggame->log_y);
    aCore->menumanager->game_log->setFont(QFont("Courier New" , aCore->conf->ggame->logfont));
}

void ButtonManager::refresh(Core *aCore) {
    if (!(aCore->inited)) return;
    //Main Interface Buttons
    this->mi_bg->refresh(0, 0, aCore->conf->gmi->scene_width, aCore->conf->gmi->scene_height);
    this->mi_intro->refresh(aCore->conf->gmi->intro_x, aCore->conf->gmi->intro_y, aCore->conf->gmi->intro_width, aCore->conf->gmi->intro_height);
    this->mi_start->refresh(aCore->conf->gmi->start_x, aCore->conf->gmi->start_y, aCore->conf->gmi->start_width, aCore->conf->gmi->start_height);
    this->mi_exit->refresh(aCore->conf->gmi->exit_x, aCore->conf->gmi->exit_y, aCore->conf->gmi->exit_width, aCore->conf->gmi->exit_height);
    this->mi_debug->refresh(aCore->conf->gmi->debug_x, aCore->conf->gmi->debug_y, aCore->conf->gmi->debug_width, aCore->conf->gmi->debug_height);
    //Introduction Buttons
    this->bi_bg->refresh(0, 0, aCore->conf->gbi->scene_width, aCore->conf->gbi->scene_height);
    this->bi_back->refresh(aCore->conf->gbi->back_x, aCore->conf->gbi->back_y, aCore->conf->gbi->back_width, aCore->conf->gbi->back_height);
    //Level Selection Buttons
    this->ls_bg->refresh(0, 0, aCore->conf->gls->scene_width, aCore->conf->gls->scene_height);
    this->ls_level_1->refresh(aCore->conf->gls->level_1_x, aCore->conf->gls->level_1_y, aCore->conf->gls->level_1_width, aCore->conf->gls->level_1_height);
    this->ls_level_2->refresh(aCore->conf->gls->level_2_x, aCore->conf->gls->level_2_y, aCore->conf->gls->level_2_width, aCore->conf->gls->level_2_height);
    this->ls_back->refresh(aCore->conf->gls->back_x, aCore->conf->gls->back_y, aCore->conf->gls->back_width, aCore->conf->gls->back_height);
    //Game Buttons
    this->game_bg->refresh(0, 0, aCore->conf->ggame->scene_width, aCore->conf->ggame->scene_height);
    this->game_cp->refresh(aCore->conf->ggame->cp_x, aCore->conf->ggame->cp_y, aCore->conf->ggame->cp_width, aCore->conf->ggame->cp_height);
    this->game_restart->refresh(aCore->conf->ggame->restart_x, aCore->conf->ggame->restart_y, aCore->conf->ggame->restart_width, aCore->conf->ggame->restart_height);
    this->game_back->refresh(aCore->conf->ggame->back_x, aCore->conf->ggame->back_y, aCore->conf->ggame->back_width, aCore->conf->ggame->back_height);
    this->game_coin->refresh(aCore->conf->ggame->coin_x, aCore->conf->ggame->coin_y, aCore->conf->ggame->coin_width, aCore->conf->ggame->coin_height);
    this->game_health->refresh(aCore->conf->ggame->health_x, aCore->conf->ggame->health_y, aCore->conf->ggame->health_width, aCore->conf->ggame->health_height);
    this->game_progressbar1->refresh(aCore->conf->ggame->progressbar_x, aCore->conf->ggame->progressbar_y, aCore->conf->ggame->progressbar_width, aCore->conf->ggame->progressbar_height);
    this->game_progressbar3->refresh(aCore->conf->ggame->progressbar_x, aCore->conf->ggame->progressbar_y, aCore->conf->ggame->progressbar_width, aCore->conf->ggame->progressbar_height);

    //Game Texts
    aCore->menumanager->game_cointext->setPos(aCore->conf->ggame->coin_x+aCore->conf->ggame->coin_width, aCore->conf->ggame->coin_y);
    aCore->menumanager->game_cointext->setFont(QFont("Courier New" , aCore->conf->ggame->coinfont, QFont::Bold));
    aCore->menumanager->game_healthtext->setPos(aCore->conf->ggame->health_x+aCore->conf->ggame->health_width, aCore->conf->ggame->health_y);
    aCore->menumanager->game_healthtext->setFont(QFont("Courier New" , aCore->conf->ggame->healthfont, QFont::Bold));
    aCore->menumanager->game_log->setPos(aCore->conf->ggame->log_x, aCore->conf->ggame->log_y);
    aCore->menumanager->game_log->setFont(QFont("Courier New" , aCore->conf->ggame->logfont));
}

void ButtonManager::clickMainInterface(Core *aCore, QGraphicsItem *citem) {
    if (this->mi_intro->isEqual(citem)) {
        aCore->menumanager->showIntroduction();
        return;
    }
    if (this->mi_start->isEqual(citem)) {
        aCore->menumanager->showLevelSelection();
        return;
    }
    if (this->mi_exit->isEqual(citem)) {
        aCore->exit();
        return;
    }
    if (this->mi_debug->isEqual(citem)) {
        aCore->menumanager->buttonmanager->toggleDebug(aCore);
        return;
    }
}

void ButtonManager::clickIntroduction(Core *aCore, QGraphicsItem *citem) {
    if (this->bi_back->isEqual(citem)) {
        aCore->menumanager->showMainInterface();
        return;
    }
}

void ButtonManager::clickLevelSelection(Core *aCore, QGraphicsItem *citem) {
    if (this->ls_level_1->isEqual(citem)) {
        aCore->gamemanager->loadLevel("level-1");
        return;
    }
    if (!aCore->lock&&this->ls_level_2->isEqual(citem)) {
        aCore->gamemanager->loadLevel("level-2");
        return;
    }
    if (this->ls_back->isEqual(citem)) {
        aCore->menumanager->showMainInterface();
        return;
    }
}

void ButtonManager::clickGame(Core *aCore, QGraphicsItem *citem) {
    if (this->game_restart->isEqual(citem)) {
        aCore->gamemanager->reloadLevel();
        return;
    }
    if (this->game_back->isEqual(citem)) {
        aCore->menumanager->showLevelSelection();
        return;
    }
    if (aCore->gamemanager->getIsInSettlement()) return;
    if (this->game_cp->isEqual(citem)) {
        aCore->gamemanager->toggleCP();
        return;
    }
    if (this->game_bt1->isEqual(citem)) {
        if (aCore->gamemanager->hasCoin(aCore->conf->tsi->tower1->upgradecost[0])) {
            aCore->gamemanager->takeCoin(aCore->conf->tsi->tower1->upgradecost[0]);
            aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->setTower(aCore->conf->tsi->tower1->towername, aCore->conf->tsi->tower1->imageurl[0], 1, aCore->conf->tsi->tower1->cooldown[0], aCore->conf->tsi->tower1->bullet[0]);
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("Plant Primary Mushroom!");
        } else {
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("You don't have enough sunshine!(Need 50)");
            aCore->audiomanager->playNotEnoughSun();
        }
        return;
    }
    if (this->game_bt2->isEqual(citem)) {
        if (aCore->gamemanager->hasCoin(aCore->conf->tsi->tower2->upgradecost[0])) {
            aCore->gamemanager->takeCoin(aCore->conf->tsi->tower2->upgradecost[0]);
            aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->setTower(aCore->conf->tsi->tower2->towername, aCore->conf->tsi->tower2->imageurl[0], 1, aCore->conf->tsi->tower2->cooldown[0], aCore->conf->tsi->tower2->bullet[0]);
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("Plant Sunflower!");
        } else {
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("You don't have enough sunshine!(Need 100)");
            aCore->audiomanager->playNotEnoughSun();
        }
        return;
    }
    if (this->game_bt3->isEqual(citem)) {
        if (aCore->gamemanager->hasCoin(aCore->conf->tsi->tower3->upgradecost[0])) {
            aCore->gamemanager->takeCoin(aCore->conf->tsi->tower3->upgradecost[0]);
            aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->setTower(aCore->conf->tsi->tower3->towername, aCore->conf->tsi->tower3->imageurl[0], 1, aCore->conf->tsi->tower3->cooldown[0], aCore->conf->tsi->tower3->bullet[0]);
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("Plant Primary PeaShooter!");
        } else {
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("You don't have enough sunshine!(Need 50)");
            aCore->audiomanager->playNotEnoughSun();
        }
        return;
    }
    if (this->game_upgrade->isEqual(citem)) {
        Tower_Data *tmptd = aCore->conf->tsi->getTower(aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->getType());
        int tmplevel = aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->getLevel();
        if (aCore->gamemanager->hasCoin(tmptd->upgradecost[tmplevel])) {
            aCore->gamemanager->takeCoin(tmptd->upgradecost[tmplevel]);
            aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->setTower(tmptd->towername, tmptd->imageurl[tmplevel], tmplevel+1, tmptd->cooldown[tmplevel], tmptd->bullet[tmplevel]);
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("Grow up!");
        } else {
            aCore->gamemanager->setSelection(-1);
            aCore->menumanager->game_log->setPlainText("You don't have enough sunshine!");
            aCore->audiomanager->playNotEnoughSun();
        }
        return;
    }
    if (this->game_remove->isEqual(citem)) {
        aCore->gamemanager->giveCoin(aCore->conf->tsi->getTower(aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->getType())->demolitionfeedback[aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->getLevel()-1]);
        aCore->gamemanager->towermanager->towers[aCore->gamemanager->getSelection()]->setTower("None", aCore->pathprefix + "image/towerposition.png", 0, 99999999, "None");
        aCore->gamemanager->setSelection(-1);
        aCore->menumanager->game_log->setPlainText("Be Removed!");
        return;
    }
    int tmp = aCore->gamemanager->getTowerID(citem);
    if (aCore->gamemanager->getSelection()==tmp)
        aCore->gamemanager->setSelection(-1);
    else
        aCore->gamemanager->setSelection(tmp);
}

AcidButton* ButtonManager::getGameBackground() {
    return this->game_bg;
}

AcidButton* ButtonManager::getGameCP() {
    return this->game_cp;
}

AcidButton* ButtonManager::getGameSelection() {
    return this->game_selection;
}

AcidButton* ButtonManager::getGameWL() {
    return this->game_wl;
}

AcidButton* ButtonManager::getGameBT1() {
    return this->game_bt1;
}

AcidButton* ButtonManager::getGameBT2() {
    return this->game_bt2;
}

AcidButton* ButtonManager::getGameBT3() {
    return this->game_bt3;
}

AcidButton* ButtonManager::getGameUpgrade() {
    return this->game_upgrade;
}

AcidButton* ButtonManager::getGameRemove() {
    return this->game_remove;
}

AcidButton* ButtonManager::getGameProgressBarInside() {
    return this->game_progressbar2;
}

AcidButton* ButtonManager::getGameProgressBarHead() {
    return this->game_progressbar4;
}

void ButtonManager::hideLock(Core *aCore) {
    if (!aCore->lock) return;
    aCore->lock = false;
    aCore->menumanager->LevelSelectionScene.removeItem(this->ls_lock->getItem());
}

void ButtonManager::toggleDebug(Core *aCore) {
    if (aCore->debug) {
        aCore->debug = false;
        this->mi_debug->setPixmap(aCore->pathprefix + "image/debug F.png");
    } else {
        aCore->debug = true;
        this->mi_debug->setPixmap(aCore->pathprefix + "image/debug T.png");
    }
}

MenuManager::MenuManager() {
    this->MainInterfaceScene.setObjectName("MainInterfaceScene");
    this->IntroductionScene.setObjectName("IntroductionScene");
    this->LevelSelectionScene.setObjectName("LevelSelectionScene");
    this->GameScene.setObjectName("GameScene");
}

MenuView* MenuManager::getView() {
    return &this->view;
}

void MenuManager::setCore(Core *aCore) {
    this->core=aCore;
}

void MenuManager::showMainInterface() {
    this->view.setScene(&this->MainInterfaceScene);
}

void MenuManager::showIntroduction() {
    this->view.setScene(&this->IntroductionScene);
}

void MenuManager::showLevelSelection() {
    this->view.setScene(&this->LevelSelectionScene);
}

void MenuManager::showGame() {
    this->view.setScene(&this->GameScene);
}

void MenuManager::init() {
    this->view.setCore(this->core);
    this->view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->view.setWindowTitle("Tower Defence");
    this->view.setWindowIcon(QIcon((this->core->pathprefix + "image/icon.png").c_str()));
    this->view.resize(this->core->conf->vi->view_width, this->core->conf->vi->view_height);
    this->view.show();
    this->buttonmanager = new ButtonManager(this->core);
}

void MenuManager::build() {
    buttonmanager->refresh(this->core);
}

void MenuManager::showReward(int treward) {
    string s;
    stringstream ss;
    ss.clear();
    ss << treward;
    ss >> s;
    this->game_log->setPlainText(("+ " + s + " sunshine!").c_str());
}
