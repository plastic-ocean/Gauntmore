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
    void _show();
    
};