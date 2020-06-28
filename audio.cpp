#include "audio.h"
#include "core.h"
#include <QMediaPlaylist>

AudioManager::AudioManager() {

}

void AudioManager::setCore(Core *aCore) {
    this->core=aCore;
}

void AudioManager::build() {
    this->BGMplaylist = new QMediaPlaylist;
    this->BGMplaylist->addMedia(QUrl("qrc:/audio/Faster1.mp3"));
    this->BGMplaylist->addMedia(QUrl("qrc:/audio/Faster2.mp3"));
    this->BGMplaylist->setPlaybackMode(QMediaPlaylist::Loop);
    this->BGMplayer = new QMediaPlayer;
    this->BGMplayer->setPlaylist(this->BGMplaylist);
    this->BGMplayer->setVolume(50);
    this->tower1effect = new QSoundEffect;
    this->tower1effect->setSource(QUrl("qrc:/audio/tower1.wav"));
    this->tower1effect->setVolume(1.0f);
    this->tower2effect = new QSoundEffect;
    this->tower2effect->setSource(QUrl("qrc:/audio/tower2.wav"));
    this->tower2effect->setVolume(1.0f);
    this->tower3effect = new QSoundEffect;
    this->tower3effect->setSource(QUrl("qrc:/audio/tower3.wav"));
    this->tower3effect->setVolume(1.0f);
    this->hitenemyeffect = new QSoundEffect;
    this->hitenemyeffect->setSource(QUrl("qrc:/audio/Fire.wav"));
    this->hitenemyeffect->setVolume(1.0f);
    this->wineffect = new QSoundEffect;
    this->wineffect->setSource(QUrl("qrc:/audio/Win.wav"));
    this->wineffect->setVolume(1.0f);
    this->loseeffect = new QSoundEffect;
    this->loseeffect->setSource(QUrl("qrc:/audio/Lose.wav"));
    this->loseeffect->setVolume(1.0f);
    this->enemydieeffect = new QSoundEffect;
    this->enemydieeffect->setSource(QUrl("qrc:/audio/enemydie.wav"));
    this->enemydieeffect->setVolume(1.0f);
    this->notenoughsuneffect = new QSoundEffect;
    this->notenoughsuneffect->setSource(QUrl("qrc:/audio/NotEnoughSun.wav"));
    this->notenoughsuneffect->setVolume(1.0f);
    this->frozeneffect = new QSoundEffect;
    this->frozeneffect->setSource(QUrl("qrc:/audio/frozen.wav"));
    this->frozeneffect->setVolume(1.0f);
    this->gainsunshineeffect = new QSoundEffect;
    this->gainsunshineeffect->setSource(QUrl("qrc:/audio/gainsunshine.wav"));
    this->gainsunshineeffect->setVolume(1.0f);
    this->buttonclickeffect = new QSoundEffect;
    this->buttonclickeffect->setSource(QUrl("qrc:/audio/buttonclick.wav"));
    this->buttonclickeffect->setVolume(1.0f);
    this->zombiecomingeffect = new QSoundEffect;
    this->zombiecomingeffect->setSource(QUrl("qrc:/audio/zombiecoming.wav"));
    this->zombiecomingeffect->setVolume(1.0f);
    this->enemyathomeeffect = new QSoundEffect;
    this->enemyathomeeffect->setSource(QUrl("qrc:/audio/enemyathome.wav"));
    this->enemyathomeeffect->setVolume(1.0f);
}

void AudioManager::playBGM() {
    this->BGMplayer->play();
}

void AudioManager::stopBGM() {
    this->BGMplayer->stop();
}

void AudioManager::playTower1() {
    //if (this->tower1effect->isPlaying()) this->tower1effect->stop();
    this->tower1effect->play();
}

void AudioManager::playTower2() {
    //if (this->tower2effect->isPlaying()) this->tower2effect->stop();
    this->tower2effect->play();
}

void AudioManager::playTower3() {
    //if (this->tower3effect->isPlaying()) this->tower3effect->stop();
    this->tower3effect->play();
}

void AudioManager::playTower(string towername) {
    if (towername=="Tower1") this->playTower1();
    if (towername=="Tower2") this->playTower2();
    if (towername=="Tower3") this->playTower3();
}

void AudioManager::playHitEnemy() {
    this->hitenemyeffect->play();
}

void AudioManager::playWin() {
    this->wineffect->play();
}

void AudioManager::playLose() {
    this->loseeffect->play();
}

void AudioManager::playEnemyDie() {
    this->enemydieeffect->play();
}

void AudioManager::playNotEnoughSun() {
    this->notenoughsuneffect->play();
}

void AudioManager::playFrozen() {
    this->frozeneffect->play();
}

void AudioManager::playGainSunshine() {
    this->gainsunshineeffect->play();
}

void AudioManager::playButtonClick() {
    this->buttonclickeffect->play();
}

void AudioManager::playZombieComing() {
    this->zombiecomingeffect->play();
}

void AudioManager::playEnemyAtHome() {
    this->enemyathomeeffect->play();
}
