#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"

using namespace oxygine;


DECLARE_SMART(PauseMenu, spPauseMenu);
class Game;
class PauseMenu : public Scene {

public:
    static spPauseMenu instance;
    
    PauseMenu();
    
    void setNewGame(string newGame) {
        // pass the new image string
    }
    
    void setQuit(string quit) {
        // pass the new image string
    }
    
private:
    spSprite _name;
    spSprite _continue;
    spSprite _newGame;
    spSprite _quit;
    
    bool _isReady;
    void _onEvent(Event *ev);
    
};
