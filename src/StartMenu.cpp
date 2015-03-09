#include "Input.h"
#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_events.h"

#include "StartMenu.h"
#include "res.h"


spStartMenu StartMenu::instance;


/**
 * Constructor.
 */
StartMenu::StartMenu():_selection(selectNewGame), _isVisible(false) {
    _background = new Sprite;
    _background->setResAnim(resources.getResAnim("start_menu_background"));
    _background->setAnchor(Vector2(0.5f, 0.5f));
    _background->setPosition(Vector2(768 / 2, 768 / 2));
    _background->attachTo(_view);
    
    _name = new Sprite;
    _name->setResAnim(resources.getResAnim("title"));
    _name->setAnchor(Vector2(0.5f, 0.5f));
    _name->setPosition(Vector2(768 / 2, (768 / 2) - _name->getHeight()));
    _name->attachTo(_view);
    
    _newGame = new Sprite;
    _newGame->setResAnim(resources.getResAnim("new_game_selected"));
    _newGame->setAnchor(Vector2(0.5f, 0.5f));
    _newGame->setPosition(Vector2(768 / 2, 768 / 2));
    _newGame->attachTo(_view);
    
    _quit = new Sprite;
    _quit->setResAnim(resources.getResAnim("quit"));
    _quit->setAnchor(Vector2(0.5f, 0.5f));
    _quit->setPosition(Vector2(768 / 2, 768 / 2 + _quit->getHeight()));
    _quit->attachTo(_view);
    
    // Add keyboard listener
    Input::instance.addEventListener(Input::event_platform, CLOSURE(this, &StartMenu::_onEvent));
}

/**
 * Keyboard event handler.
 *
 * @ev is the SDL event sent by the event listener.
 */
void StartMenu::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && _isVisible) {
        switch (event->key.keysym.sym) {
            case SDLK_RETURN:
                if (_selection == selectNewGame) {
                    _isVisible = false;
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
void StartMenu::_selectNext() {
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

void StartMenu::_show() {
    _isVisible = true;
}
