#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
//#include "SoundPlayer.h"
//#include "SoundSystem.h"
//#include "SoundInstance.h"
#include "GameScene.h"
#include "PauseMenu.h"
#include "StartMenu.h"
#include "res.h"


using namespace oxygine;

class Gauntmore {
    
public:
    Gauntmore();
    
    void init();
    void update();
    void destroy();
    int mainLoop();
    
//    SoundPlayer getMusicPlayer() {
//        return _musicPlayer;
//    }
    
private:
//    SoundPlayer _musicPlayer;
};