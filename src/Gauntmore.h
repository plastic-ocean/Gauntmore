#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
#include "res.h"
#include "GameScene.h"

#include "SoundPlayer.h"
#include "SoundSystem.h"
#include "SoundInstance.h"

using namespace oxygine;

class Gauntmore {
    
public:
    Gauntmore();
    
    int mainLoop();
    void initGauntmore();
    void updateGauntmore();
    void destroyGauntmore();
    
    SoundPlayer getMusicPlayer() {
        return _musicPlayer;
    }
    
private:
    SoundPlayer _musicPlayer;
};