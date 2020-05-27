#ifndef MENU_H
#define MENU_H
#include "core.h"
#include <QGraphicsView>
#include <QMouseEvent>
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
};

class ButtonManager {
private:
    AcidButton *mi_bg, *mi_intro, *mi_start, *mi_exit;
    AcidButton *ls_bg, *ls_level_1, *ls_level_2;
public:
    ButtonManager(Core *aCore);
    void refresh(Core *aCore);
    void clickMainInterface(Core *aCore, QGraphicsItem *citem);
};

class MenuManager {
private:
    Core *core;
    MenuView view;
public:
    ButtonManager *buttonmanager;
    QGraphicsScene MainInterfaceScene, LevelSelectionScene;
    MenuManager();
    void setCore(Core *aCore);
    void showMainInterface();
    void showLevelSelection();
    void init();
    void build();
};

QGraphicsRectItem* createAcidButton(string path, int ABwidth, int ABheight);

#endif // MENU_H
