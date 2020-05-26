#ifndef CORE_H
#define CORE_H
#include "menu.h"
#include <string>
using namespace  std;

class MenuManager;
class Core {
public:
    string pathprefix;
    MenuManager* menumanager;
    Core();
};

#endif // CORE_H
