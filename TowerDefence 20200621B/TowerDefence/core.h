#ifndef CORE_H
#define CORE_H
#include <string>
#include <QApplication>
using namespace  std;

class Config;
class MenuManager;
class AudioManager;
class GameManager;

class Core {
private:
    QApplication *app;
public:
    bool inited = false;
    string pathprefix;
    Config *conf;
    MenuManager *menumanager;
    AudioManager *audiomanager;
    GameManager *gamemanager;
    Core(QApplication *a);
    void resize(int newwidth, int newheight);
    void exit();
};

#endif // CORE_H
