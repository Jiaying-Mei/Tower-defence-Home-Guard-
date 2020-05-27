#ifndef CONFIG_H
#define CONFIG_H

class Core;

class View_Info {
public:
    View_Info();
    void build(double wratio, double hratio);
    int view_width, view_height;
};

class GUI_MI {
public:
    GUI_MI();
    void build(double wratio, double hratio);
    int scene_width, scene_height;
    int intro_width, intro_height, intro_x, intro_y;
    int start_width, start_height, start_x, start_y;
    int exit_width, exit_height, exit_x, exit_y;
};

class GUI_LS {
public:
    GUI_LS();
    void build(double wratio, double hratio);
    int scene_width, scene_height;
    int level_1_width, level_1_height, level_1_x, level_1_y;
    int level_2_width, level_2_height, level_2_x, level_2_y;
};

class Config {
private:
    Core *core;
public:
    double nowwratio=1.0, nowhratio=1.0;
    //double nowwratio=0.5, nowhratio=0.5;
    Config();
    void setCore(Core *aCore);
    void build();
    View_Info *vi;
    GUI_MI *gmi;
    GUI_LS *gls;
};

#endif // CONFIG_H
