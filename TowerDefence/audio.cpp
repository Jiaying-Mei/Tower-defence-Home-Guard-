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
}

void AudioManager::playBGM() {
    this->BGMplayer->play();
}

void AudioManager::stopBGM() {
    this->BGMplayer->stop();
}
