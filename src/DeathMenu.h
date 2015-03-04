#pragma once
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"

using namespace oxygine;


DECLARE_SMART(DeathMenu, spDeathMenu);
class Game;
class DeathMenu : public Scene {
    
public:
    static spDeathMenu instance;
    enum Selection {selectNewGame, selectQuit};
    
    DeathMenu();
    
    
    /* Getters and setters */
    
    void setNewGame(string newGameImage) {
        _newGame->setResAnim(resources.getResAnim(newGameImage));
    }
    
    void setQuit(string quitImage) {
        _quit->setResAnim(resources.getResAnim(quitImage));
    }
    
    void setGame(Game *game) {
        _game = game;
    }
    
private:
    Game *_game;
    Selection _selection;
    spSprite _deathBackground;
    spSprite _name;
    spSprite _youDied;
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
