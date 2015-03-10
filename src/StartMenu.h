#pragma once
#include "Menu.h"
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"

using namespace oxygine;


DECLARE_SMART(StartMenu, spStartMenu);
class StartMenu : public Menu {
    
public:
    static spStartMenu instance;
    enum Selection {selectNewGame, selectQuit};
    
    StartMenu();
    
private:
    Selection _selection;
    spSprite _background;
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