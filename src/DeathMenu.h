#pragma once
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"

using namespace oxygine;


DECLARE_SMART(DeathMenu, spDeathMenu);
class Game;
class DeathMenu : public Menu {
    
public:
    static spDeathMenu instance;
    enum Selection {selectNewGame, selectQuit};
    
    DeathMenu();
    
private:
    Selection _selection;
    spSprite _deathBackground;
    spSprite _youDied;
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
    
    /**
     * Sets the menu to visible when shown. Used for handling input.
     */
    void _show();
    
};
