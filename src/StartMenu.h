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
    
    void setNewGame(string newGameImage) {
        _newGame->setResAnim(resources.getResAnim(newGameImage));
    }
    
//    void setContinue(string continueImage) {
//        _continue->setResAnim(resources.getResAnim(continueImage));
//    }
    
    void setQuit(string quitImage) {
        _quit->setResAnim(resources.getResAnim(quitImage));
    }
    
private:
    Selection _selection;
    spSprite _name;
//    spSprite _continue;
    spSprite _newGame;
    spSprite _quit;
    
    /**
     * Keyboard event handler.
     *
     * @ev is the SDL event sent by the event listener.
     */
    void _onEvent(Event *ev);
    
    /**
     * Selects the next item in the menu list.
     */
    void selectNext();

};