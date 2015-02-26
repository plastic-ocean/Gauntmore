#include "Gauntmore.h"


/**
 * Constructor.
 */
Gauntmore::Gauntmore() {}


/**
 * Load resources, initialize the game, and attach it to the stage.
 */
void Gauntmore::init() {
    // Initialize sound system
//    SoundSystem::instance = SoundSystem::create();
//    SoundSystem::instance->init(16);
//    SoundPlayer::initialize();
//
    // Load resources.
    loadResources();
    
    // Create game scene.
    GameScene::instance = new GameScene;
    
    // Setup music player and play music.
//    _musicPlayer.play(resSounds.get("music"));
    
    GameScene::instance->show();
}


/**
 * Global update method. Called every frame.
 */
void Gauntmore::update() {
//    SoundSystem::instance->update();
//    _musicPlayer.update();
}


/**
 * Free all allocated resources and delete all created actors.
 */
void Gauntmore::destroy() {
//    _musicPlayer.stop();
//    SoundSystem::instance->stop();
    GameScene::instance = 0;
    freeResources();
//    SoundSystem::instance->release();
}


/**
 * The main loop method. Called each frame.
 */
int Gauntmore::mainLoop() {
    update();
    // Update our stage and all actors. Actor::update is called for all children.
    getStage()->update();
    
    if (core::beginRendering()) {
        Color clearColor(32, 32, 32, 255);
        Rect viewport(Point(0, 0), core::getDisplaySize());
        // Render all actors. Actor::render is called for all children.
        getStage()->render(clearColor, viewport);
        
        core::swapDisplayBuffers();
    }
    
    // Update internal components. All input events are passed to Stage::instance.handleEvent.
    // If done is true then User requests quit from app.
    bool done = core::update();
    
    return done ? 1 : 0;
}
