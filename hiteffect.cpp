#include "game.h"

class Core;

void HitEffect::remove(Core *aCore) {
    aCore->menumanager->GameScene.removeItem(this->getItem());
}

void HitEffect::increaseNowTick() {
    this->nowtick++;
}

bool HitEffect::isDurationExceeded() {
    return this->nowtick>=this->duration;
}

void HitEffect::refreshH() {
    this->refresh((int)(this->x*this->co->nowwratio), (int)(this->y*this->co->nowhratio), (int)(this->w*this->co->nowwratio), (int)(this->h*this->co->nowhratio));
}

void HitEffectManager::setCore(Core *aCore) {
    this->core = aCore;
}

HitEffect* HitEffectManager::getHitEffect11(AcidPoint hiteffectcenter) {
    HitEffect* tmp = new HitEffect(this->core->conf, this->core->conf->hei->hiteffect11, &this->core->menumanager->GameScene, hiteffectcenter.x-this->core->conf->ggame->hiteffect_dx, hiteffectcenter.y-this->core->conf->ggame->hiteffect_dy, this->core->conf->ggame->hiteffect_width, this->core->conf->ggame->hiteffect_height);
    return tmp;
}

HitEffect* HitEffectManager::getHitEffect12(AcidPoint hiteffectcenter) {
    HitEffect* tmp = new HitEffect(this->core->conf, this->core->conf->hei->hiteffect12, &this->core->menumanager->GameScene, hiteffectcenter.x-this->core->conf->ggame->hiteffect_dx, hiteffectcenter.y-this->core->conf->ggame->hiteffect_dy, this->core->conf->ggame->hiteffect_width, this->core->conf->ggame->hiteffect_height);
    return tmp;
}

HitEffect* HitEffectManager::getHitEffect21(AcidPoint hiteffectcenter) {
    HitEffect* tmp = new HitEffect(this->core->conf, this->core->conf->hei->hiteffect21, &this->core->menumanager->GameScene, hiteffectcenter.x-this->core->conf->ggame->hiteffect_dx, hiteffectcenter.y-this->core->conf->ggame->hiteffect_dy, this->core->conf->ggame->hiteffect_width, this->core->conf->ggame->hiteffect_height);
    return tmp;
}

HitEffect* HitEffectManager::getHitEffect31(AcidPoint hiteffectcenter) {
    HitEffect* tmp = new HitEffect(this->core->conf, this->core->conf->hei->hiteffect31, &this->core->menumanager->GameScene, hiteffectcenter.x-this->core->conf->ggame->hiteffect_dx, hiteffectcenter.y-this->core->conf->ggame->hiteffect_dy, this->core->conf->ggame->hiteffect_width, this->core->conf->ggame->hiteffect_height);
    return tmp;
}

HitEffect* HitEffectManager::getHitEffect32(AcidPoint hiteffectcenter) {
    HitEffect* tmp = new HitEffect(this->core->conf, this->core->conf->hei->hiteffect32, &this->core->menumanager->GameScene, hiteffectcenter.x-this->core->conf->ggame->hiteffect_dx, hiteffectcenter.y-this->core->conf->ggame->hiteffect_dy, this->core->conf->ggame->hiteffect_width, this->core->conf->ggame->hiteffect_height);
    return tmp;
}

HitEffect* HitEffectManager::getHitEffect33(AcidPoint hiteffectcenter) {
    HitEffect* tmp = new HitEffect(this->core->conf, this->core->conf->hei->hiteffect33, &this->core->menumanager->GameScene, hiteffectcenter.x-this->core->conf->ggame->hiteffect_dx, hiteffectcenter.y-this->core->conf->ggame->hiteffect_dy, this->core->conf->ggame->hiteffect_width, this->core->conf->ggame->hiteffect_height);
    return tmp;
}

HitEffect* HitEffectManager::getHitEffect(string targethiteffect, AcidPoint hiteffectcenter) {
    if (targethiteffect=="hiteffect11")
        return this->getHitEffect11(hiteffectcenter);
    if (targethiteffect=="hiteffect12")
        return this->getHitEffect12(hiteffectcenter);
    if (targethiteffect=="hiteffect21")
        return this->getHitEffect21(hiteffectcenter);
    if (targethiteffect=="hiteffect31")
        return this->getHitEffect31(hiteffectcenter);
    if (targethiteffect=="hiteffect32")
        return this->getHitEffect32(hiteffectcenter);
    if (targethiteffect=="hiteffect33")
        return this->getHitEffect33(hiteffectcenter);
    return NULL;
}

AcidPoint getPoint(Core *aCore, Bullet *b, Enemy *e) {
    AcidPoint ap1 = e->getCenter(aCore), ap2= b->getCenter();
    return AcidPoint((int)(ap1.x*0.85+ap2.x*0.15), (int)(ap1.y*0.85+ap2.y*0.15));
}

void HitEffectManager::addHitEffect(Bullet *bullet, Enemy *enemy) {
    HitEffect *tmp = this->getHitEffect(bullet->getHitEffect(), getPoint(this->core, bullet, enemy));
    this->hiteffects.push_back(tmp);
}

void HitEffectManager::removeAllHitEffects() {
    for (vector<HitEffect*>::iterator it = this->hiteffects.begin(); it!= this->hiteffects.end(); it++) {
        (*it)->remove(this->core);
        delete *it;
    }
    this->hiteffects.clear();
}

void HitEffectManager::refreshAllHitEffects() {
    for (HitEffect* he:this->hiteffects)
        he->refreshH();
}

void HitEffectManager::run() {
    if (this->hiteffects.empty()) return;
    queue<HitEffect*> tmp;
    while (tmp.size()) tmp.pop();
    for (HitEffect* he:this->hiteffects)
        if (he) {
            he->increaseNowTick();
            if (he->isDurationExceeded()) {
                he->remove(this->core);
                delete he;
            } else {
                tmp.push(he);
            }
        }
    if (tmp.size()==this->hiteffects.size()) return;
    this->hiteffects.clear();
    if (tmp.empty()) return;
    while (tmp.size()) {
        this->hiteffects.push_back(tmp.front());
        tmp.pop();
    }
}
