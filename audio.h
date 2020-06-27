#ifndef AUDIO_H
#define AUDIO_H
#include <QMediaPlayer>
#include <QSoundEffect>
#include <string>
using namespace std;

class Core;
class QSoundEffect;

class AudioManager {
private:
    Core *core;
    QMediaPlaylist *BGMplaylist;
    QMediaPlayer *BGMplayer;
    QSoundEffect *tower1effect, *tower2effect, *tower3effect, *hitenemyeffect, *wineffect, *loseeffect, *enemydieeffect, *notenoughsuneffect;
public:
    AudioManager();
    void setCore(Core *aCore);
    void build();
    void playBGM();
    void stopBGM();
    void playTower1();
    void playTower2();
    void playTower3();
    void playTower(string towername);
    void playHitEnemy();
    void playWin();
    void playLose();
    void playEnemyDie();
    void playNotEnoughSun();
};

#endif // AUDIO_H
