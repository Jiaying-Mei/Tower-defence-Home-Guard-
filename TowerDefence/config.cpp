#include "config.h"

View_Info::View_Info() {

}

void View_Info::build(double wratio, double hratio) {
    this->view_width = (int)(3000*wratio);
    this->view_height = (int)(2000*hratio);
}

GUI_MI::GUI_MI() {

}

void GUI_MI::build(double wratio, double hratio) {
    this->scene_width = (int)(3000*wratio);
    this->scene_height = (int)(2000*hratio);
    this->intro_x = (int)(1049*wratio);
    this->intro_y = (int)(500*hratio);
    this->intro_width = (int)(902*wratio);
    this->intro_height = (int)(200*hratio);
    this->start_x = (int)(1104*wratio);
    this->start_y = (int)(900*hratio);
    this->start_width = (int)(792*wratio);
    this->start_height = (int)(200*hratio);
    this->exit_x = (int)(1130*wratio);
    this->exit_y = (int)(1300*hratio);
    this->exit_width = (int)(740*wratio);
    this->exit_height = (int)(200*hratio);
}

GUI_LS::GUI_LS() {

}

void GUI_LS::build(double wratio, double hratio) {
    this->scene_width = (int)(3000*wratio);
    this->scene_height = (int)(2000*hratio);
    this->level_1_x = (int)(150*wratio);
    this->level_1_y = (int)(620*hratio);
    this->level_1_width = (int)(1300*wratio);
    this->level_1_height = (int)(1475*hratio);
    //非对称布局 = =
    this->level_2_x = (int)(1575*wratio);
    this->level_2_y = (int)(620*hratio);
    this->level_2_width = (int)(1300*wratio);
    this->level_2_height = (int)(1475*hratio);
}


Config::Config() {
    this->vi = new View_Info;
    this->gmi = new GUI_MI;
    this->gls = new GUI_LS;
}

void Config::setCore(Core *aCore) {
    this->core=aCore;
}

void Config::build() {
    double targetwratio = this->nowwratio;
    double targethratio = this->nowhratio;
    this->vi->build(targetwratio, targethratio);
    this->gmi->build(targetwratio, targethratio);
    this->gls->build(targetwratio, targethratio);
}
