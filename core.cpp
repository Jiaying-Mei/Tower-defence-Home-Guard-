#include "core.h"
#include "menu.h"
#include <string>
using namespace  std;

Core::Core()
{
    this->pathprefix = ":/";
    this->menumanager = new MenuManager;
    this->menumanager->setCore(this);
    this->menumanager->build();
    this->menumanager->showMainInterface();
}
