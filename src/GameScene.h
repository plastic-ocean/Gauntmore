#pragma once
#include "Scene.h"
#include "Game.h"
#include "PauseMenu.h"

DECLARE_SMART(GameScene, spGameScene);
class GameScene: public Scene {
    
public:
    static spGameScene instance;
    GameScene();
    
    void pauseGame();
    
    bool isPaused() {
        return _isPaused;
    }
    
private:
    spGame _game;
    bool _isPaused;
    void _onEvent(Event *ev);
    void _show();
    
};