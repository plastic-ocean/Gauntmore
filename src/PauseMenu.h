#pragma once
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"

using namespace oxygine;


DECLARE_SMART(PauseMenu, spPauseMenu);
class PauseMenu : public Scene {

public:
    static spPauseMenu instance;
    enum Selection {selectContinue, selectNewGame, selectQuit};
    
    PauseMenu();
    
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
    Selection _selection;
    spSprite _name;
    spSprite _continue;
    spSprite _newGame;
    spSprite _quit;
    bool _isReady;
    
    /**
     * Keyboard event handler.
     *
     * @ev is the SDL event sent by the event listener.
     */
    void _onEvent(Event *ev);
    
    /**
     * Selects the next item in the menu list.
     */
    void _selectNext(string direction);
    
};
