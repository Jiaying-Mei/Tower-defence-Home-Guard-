#ifndef MENU_H
#define MENU_H
#include "core.h"
#include <QGraphicsView>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <map>
using namespace std;

class Core;
class MenuView:public QGraphicsView {
private:
    Core *core;
    Q_OBJECT
public:
    explicit MenuView(QWidget *parent=0);
    void setCore(Core *aCore);
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
};

class AcidButton {
private:
    QGraphicsRectItem *bitem;
    string bname;
    QPixmap bimage;
public:
    AcidButton(string tname, string tpath, QGraphicsScene *tscene, int pos_x, int pos_y, int ABwidth, int ABheight);
    bool isEqual(QGraphicsItem *oitem);
    void refresh(int pos_x, int pos_y, int ABwidth, int ABheight);
    void setPixmap(string tpath);
    QGraphicsRectItem* getItem();
};

class ButtonManager {
private:
    AcidButton *mi_bg, *mi_intro, *mi_start, *mi_exit;
    AcidButton *bi_bg, *bi_back;
    AcidButton *ls_bg, *ls_level_1, *ls_level_2, *ls_back;
    AcidButton *game_bg, *game_cp, *game_restart, *game_back, *game_selection, *game_coin, *game_health, *game_wl, *game_bt1, *game_bt2, *game_bt3, *game_upgrade, *game_remove;
public:
    ButtonManager(Core *aCore);
    void refresh(Core *aCore);
    void clickMainInterface(Core *aCore, QGraphicsItem *citem);
    void clickIntroduction(Core *aCore, QGraphicsItem *citem);
    void clickLevelSelection(Core *aCore, QGraphicsItem *citem);
    void clickGame(Core *aCore, QGraphicsItem *citem);
    AcidButton* getGameBackground();
    AcidButton* getGameCP();
    AcidButton* getGameSelection();
    AcidButton* getGameWL();
    AcidButton* getGameBT1();
    AcidButton* getGameBT2();
    AcidButton* getGameBT3();
    AcidButton* getGameUpgrade();
    AcidButton* getGameRemove();
};

class MenuManager {
private:
    Core *core;
    MenuView view;
public:
    ButtonManager *buttonmanager;
    QGraphicsScene MainInterfaceScene, IntroductionScene, LevelSelectionScene, GameScene;
    QGraphicsTextItem *game_cointext, *game_healthtext, *game_log;
    MenuManager();
    MenuView* getView();
    void setCore(Core *aCore);
    void showMainInterface();
    void showIntroduction();
    void showLevelSelection();
    void showGame();
    void init();
    void build();
    void showReward(int treward);
};

QGraphicsRectItem* createAcidButton(string path, int ABwidth, int ABheight);

#endif // MENU_H
