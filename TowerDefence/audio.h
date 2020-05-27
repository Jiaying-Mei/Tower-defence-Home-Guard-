#ifndef AUDIO_H
#define AUDIO_H
#include <QMediaPlayer>

class Core;

class AudioManager {
private:
    Core *core;
    QMediaPlaylist *BGMplaylist;
    QMediaPlayer *BGMplayer;
public:
    AudioManager();
    void setCore(Core *aCore);
    void build();
    void playBGM();
    void stopBGM();
};

#endif // AUDIO_H
