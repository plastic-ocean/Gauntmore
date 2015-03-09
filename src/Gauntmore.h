#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
//#include "SoundPlayer.h"
//#include "SoundSystem.h"
//#include "SoundInstance.h"
#include "GameScene.h"
#include "PauseMenu.h"
#include "StartMenu.h"
#include "DeathMenu.h"
#include "res.h"


using namespace oxygine;

class Gauntmore {
    
public:
    Gauntmore();
    
    /**
     * Load resources, initialize the game, and attach it to the stage.
     */
    void init();
    
    /**
     * Global update method. Called every frame.
     */
    void update();
    
    /**
     * Free all allocated resources and delete all created actors.
     */
    void destroy();
    
    /**
     * The main loop method. Called each frame.
     */
    int mainLoop();
    
    /**
     * Gets the music player.
     */
//    SoundPlayer getMusicPlayer();
    
private:
//    SoundPlayer _musicPlayer;
};