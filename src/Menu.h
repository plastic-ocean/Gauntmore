#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"

using namespace oxygine;


DECLARE_SMART(Menu, spMenu);
//class Game;
class Menu : public Scene {
    
public:
    Menu();
    
    /* Getters and setters */
    
    /**
     * Changes the new game image between selected and unselected.
     */
    void setNewGame(string newGameImage);
    
    /**
     * Changes the continue image between selected and unselected.
     */
    void setContinue(string continueImage);
    
    /**
     * Changes the quit image between selected and unselected.
     */
    void setQuit(string quitImage);
    
    /**
     * Sets the game.
     */
    void setGame(Game *game);
    
protected:
    Game *_game;
    spSprite _name;
    spSprite _newGame;
    spSprite _continue;
    spSprite _quit;
};
