#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"

using namespace oxygine;


DECLARE_SMART(StartMenu, spStartMenu);
class Game;
class StartMenu : public Scene {
    
public:
    static spStartMenu instance;
    enum Selection {selectNewGame, selectQuit};
    
    StartMenu();
    
    
    /* Getters and setters */
    
    void setNewGame(string newGameImage);
    
    void setQuit(string quitImage);
    
private:
    Selection _selection;
    spSprite _background;
    spSprite _name;
    spSprite _newGame;
    spSprite _quit;
    bool _isVisible;
    
    /**
     * Keyboard event handler.
     *
     * @ev is the SDL event sent by the event listener.
     */
    void _onEvent(Event *ev);
    
    /**
     * Selects the next item in the menu list.
     */
    void _selectNext();
    
    void _show();

};