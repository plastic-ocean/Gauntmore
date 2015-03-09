#include "Input.h"
#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_events.h"

#include "DeathMenu.h"
#include "res.h"


spDeathMenu DeathMenu::instance;


/**
 * Constructor.
 */
DeathMenu::DeathMenu():_selection(selectNewGame), _isVisible(false) {
    _deathBackground = new Sprite;
    _deathBackground->setResAnim(resources.getResAnim("death_background"));
    _deathBackground->setAnchor(Vector2(0.5f, 0.5f));
    _deathBackground->setPosition(Vector2(768 / 2, 768 / 2));
    _deathBackground->attachTo(_view);
    
    _name = new Sprite;
    _name->setResAnim(resources.getResAnim("title_small"));
    _name->setAnchor(Vector2(0.5f, 0.5f));
    _name->setPosition(Vector2(768 / 2, _name->getHeight()));
    _name->attachTo(_view);
    
    _youDied = new Sprite;
    _youDied->setResAnim(resources.getResAnim("you_died"));
    _youDied->setAnchor(Vector2(0.5f, 0.5f));
    _youDied->setPosition(Vector2(768 / 2, (768 / 2) - _name->getHeight()));
    _youDied->attachTo(_view);
    
    _newGame = new Sprite;
    _newGame->setResAnim(resources.getResAnim("new_game_selected"));
    _newGame->setAnchor(Vector2(0.5f, 0.5f));
    _newGame->setPosition(Vector2(768 / 2, 768 / 2 + 50));
    _newGame->attachTo(_view);
    
    _quit = new Sprite;
    _quit->setResAnim(resources.getResAnim("quit"));
    _quit->setAnchor(Vector2(0.5f, 0.5f));
    _quit->setPosition(Vector2(768 / 2, 768 / 2 + _quit->getHeight() + 50));
    _quit->attachTo(_view);
    
    // Add escape key listener
    Input::instance.addEventListener(Input::event_platform, CLOSURE(this, &DeathMenu::_onEvent));
}


void DeathMenu::setNewGame(string newGameImage) {
    _newGame->setResAnim(resources.getResAnim(newGameImage));
}

void DeathMenu::setQuit(string quitImage) {
    _quit->setResAnim(resources.getResAnim(quitImage));
}

void DeathMenu::setGame(Game *game) {
    _game = game;
}


/**
 * Keyboard event handler.
 *
 * @ev is the SDL event sent by the event listener.
 */
void DeathMenu::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && _isVisible) {
        switch (event->key.keysym.sym) {
            case SDLK_RETURN:
                if (_selection == selectNewGame) {
                    _isVisible = false;
                    _game->createNewGame();
                    changeScene(GameScene::instance);
                } else if (_selection == selectQuit) {
                    core::requestQuit();
                }
                break;
            case SDLK_UP:
            case SDLK_w:
            case SDLK_DOWN:
            case SDLK_s:
            case SDLK_TAB:
                _selectNext();
                break;
            default:
                break;
        }
    }
}


/**
 * Selects the next item in the menu list.
 */
void DeathMenu::_selectNext() {
    if (_selection == selectNewGame) {
        _selection = selectQuit;
        setQuit("quit_selected");
        setNewGame("new_game");
    } else if (_selection == selectQuit) {
        _selection = selectNewGame;
        setQuit("quit");
        setNewGame("new_game_selected");
    }
}


void DeathMenu::_show() {
    _isVisible = true;
}
