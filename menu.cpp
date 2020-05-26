#include "menu.h"
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QIcon>
#include <QPixmap>
#include <map>
using namespace std;
#include <QDebug>
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
        QPointF itemPos = item->pos();
        if (scene()->objectName()=="MainInterfaceScene") {
            if (itemPos==QPointF(1104,900))
                this->core->menumanager->showLevelSelection();
        }
    }
}

MenuManager::MenuManager()
{

}
void MenuManager::setCore(Core *aCore) {
    this->core=aCore;
}
void MenuManager::showMainInterface() {
    this->view.setScene(&this->MainInterfaceScene);
}
void MenuManager::showLevelSelection() {
    this->view.setScene(&this->LevelSelectionScene);
}
void MenuManager::build() {
    this->view.setCore(this->core);
    this->view.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->view.setWindowTitle("Tower Defence");
    this->view.setWindowIcon(QIcon((this->core->pathprefix + "images/icon.png").c_str()));
    this->view.resize(3000,2000);
    this->view.show();
    this->MainInterfaceScene.setObjectName("MainInterfaceScene");
    QGraphicsRectItem *item;
    item = createAcidButton(this->core->pathprefix + "images/main interface.jpg",3000,2000);
    this->MainInterfaceScene.addItem(item);
    //this->MainInterfaceScene.setBackgroundBrush(QPixmap((this->core->pathprefix + "images/main interface.jpg").c_str()).scaled(QSize(3000,2000)));
    item = createAcidButton(this->core->pathprefix + "images/start icon.png",792,200);
    this->MainInterfaceScene.addItem(item);
    item->setPos(1104,900);
    item = createAcidButton(this->core->pathprefix + "images/intro icon.png",902,200);
    this->MainInterfaceScene.addItem(item);
    item->setPos(1049,500);
    item = createAcidButton(this->core->pathprefix + "images/exit icon.png",740,200);
    this->MainInterfaceScene.addItem(item);
    item->setPos(1130,1300);

    this->LevelSelectionScene.setObjectName("LevelSelectionScene");
    item = createAcidButton(this->core->pathprefix + "images/level selection.png",3000,2000);
    this->LevelSelectionScene.addItem(item);
    //this->LevelSelectionScene.setBackgroundBrush(QPixmap((this->core->pathprefix + "images/level selection.png").c_str()).scaled(QSize(3000,2000)));
}
