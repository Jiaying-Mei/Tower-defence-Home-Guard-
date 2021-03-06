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
