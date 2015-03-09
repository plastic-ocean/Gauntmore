#pragma once
#include "Scene.h"
#include "Game.h"
#include "PauseMenu.h"

DECLARE_SMART(GameScene, spGameScene);
class GameScene: public Scene {
    
public:
    static spGameScene instance;
    
    GameScene();
    
private:
    spGame _game;
    
    /**
     * Unpauses the game when switching to this scene.
     */
    void _show();
};