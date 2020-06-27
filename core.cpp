#include "core.h"
#include "config.h"
#include "menu.h"
#include "audio.h"
#include "game.h"
#include <string>
using namespace  std;

Core::Core(QApplication *a) {
    this->app = a;
    this->pathprefix = ":/";
    this->conf = new Config;
    this->conf->setCore(this);
    this->conf->build();
    this->menumanager = new MenuManager;
    this->menumanager->setCore(this);
    this->menumanager->init();
    this->menumanager->build();
    this->menumanager->showMainInterface();
    this->audiomanager = new AudioManager;
    this->audiomanager->setCore(this);
    this->audiomanager->build();
    this->audiomanager->playBGM();
    this->gamemanager = new GameManager;
    this->gamemanager->setCore(this);
    this->inited = true;
}

void Core::resize(int newwidth, int newheight) {
    this->conf->nowwratio = newwidth / 3000.;
    this->conf->nowhratio = newheight / 2000.;
    this->conf->build();
    if (!this->inited) return;
    this->menumanager->build();
    this->gamemanager->refresh();
}

void Core::exit() {
    if (this->inited) this->app->exit();
}
