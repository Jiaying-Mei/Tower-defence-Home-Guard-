#include "menu.h"
#include "config.h"
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
        if (scene()->objectName()=="MainInterfaceScene")
            this->core->menumanager->buttonmanager->clickMainInterface(this->core, item);
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

ButtonManager::ButtonManager(Core *aCore) {
    //Main Interface Buttons
    this->mi_bg = new AcidButton("mi bg", aCore->pathprefix + "image/main interface.jpg", &aCore->menumanager->MainInterfaceScene,0, 0, aCore->conf->gmi->scene_width, aCore->conf->gmi->scene_height);
    this->mi_intro = new AcidButton("mi intro", aCore->pathprefix + "image/intro icon.png", &aCore->menumanager->MainInterfaceScene, aCore->conf->gmi->intro_x, aCore->conf->gmi->intro_y, aCore->conf->gmi->intro_width, aCore->conf->gmi->intro_height);
    this->mi_start = new AcidButton("mi start", aCore->pathprefix + "image/start icon.png", &aCore->menumanager->MainInterfaceScene, aCore->conf->gmi->start_x, aCore->conf->gmi->start_y, aCore->conf->gmi->start_width, aCore->conf->gmi->start_height);
    this->mi_exit = new AcidButton("mi exit", aCore->pathprefix + "image/exit icon.png", &aCore->menumanager->MainInterfaceScene, aCore->conf->gmi->exit_x, aCore->conf->gmi->exit_y, aCore->conf->gmi->exit_width, aCore->conf->gmi->exit_height);
    //Level Selection Buttons
    this->ls_bg = new AcidButton("ls bg", aCore->pathprefix + "image/level selection.png", &aCore->menumanager->LevelSelectionScene, 0, 0, aCore->conf->gls->scene_width, aCore->conf->gls->scene_height);
    this->ls_level_1 = new AcidButton("ls level_1", aCore->pathprefix + "image/level_1 icon.png", &aCore->menumanager->LevelSelectionScene, aCore->conf->gls->level_1_x, aCore->conf->gls->level_1_y, aCore->conf->gls->level_1_width, aCore->conf->gls->level_1_height);
    this->ls_level_2 = new AcidButton("ls level_2", aCore->pathprefix + "image/level_2 icon.png", &aCore->menumanager->LevelSelectionScene, aCore->conf->gls->level_2_x, aCore->conf->gls->level_2_y, aCore->conf->gls->level_2_width, aCore->conf->gls->level_2_height);
}

void ButtonManager::refresh(Core *aCore) {
    if (!(aCore->inited)) return;
    //Main Interface Buttons
    this->mi_bg->refresh(0, 0, aCore->conf->gmi->scene_width, aCore->conf->gmi->scene_height);
    this->mi_intro->refresh(aCore->conf->gmi->intro_x, aCore->conf->gmi->intro_y, aCore->conf->gmi->intro_width, aCore->conf->gmi->intro_height);
    this->mi_start->refresh(aCore->conf->gmi->start_x, aCore->conf->gmi->start_y, aCore->conf->gmi->start_width, aCore->conf->gmi->start_height);
    this->mi_exit->refresh(aCore->conf->gmi->exit_x, aCore->conf->gmi->exit_y, aCore->conf->gmi->exit_width, aCore->conf->gmi->exit_height);
    //Level Selection Buttons
    this->ls_bg->refresh(0, 0, aCore->conf->gls->scene_width, aCore->conf->gls->scene_height);
    this->ls_level_1->refresh(aCore->conf->gls->level_1_x, aCore->conf->gls->level_1_y, aCore->conf->gls->level_1_width, aCore->conf->gls->level_1_height);
    this->ls_level_2->refresh(aCore->conf->gls->level_2_x, aCore->conf->gls->level_2_y, aCore->conf->gls->level_2_width, aCore->conf->gls->level_2_height);
}

void ButtonManager::clickMainInterface(Core *aCore, QGraphicsItem *citem) {
    if (this->mi_intro->isEqual(citem)) {

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
}

MenuManager::MenuManager() {
    this->MainInterfaceScene.setObjectName("MainInterfaceScene");
    this->LevelSelectionScene.setObjectName("LevelSelectionScene");
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
