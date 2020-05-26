#ifndef MENU_H
#define MENU_H
#include "core.h"
#include <QGraphicsView>
#include <QMouseEvent>
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
};

class MenuManager {
private:
    Core *core;
    MenuView view;
    QGraphicsScene MainInterfaceScene, LevelSelectionScene;
public:
    MenuManager();
    void setCore(Core *aCore);
    void showMainInterface();
    void showLevelSelection();
    void build();
};

QGraphicsRectItem* createAcidButton(string path, int ABwidth, int ABheight);

#endif // MENU_H
