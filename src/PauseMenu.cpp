#include "Input.h"
#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_events.h"

#include "PauseMenu.h"
#include "res.h"


spPauseMenu PauseMenu::instance;


/**
 * Constructor.
 */
PauseMenu::PauseMenu():_isReady(false), _selection(selectContinue) {
    _name = new Sprite;
    _name->setResAnim(resources.getResAnim("title_small"));
    _name->setAnchor(Vector2(0.5f, 0.5f));
    _name->setPosition(Vector2(768 / 2, _name->getHeight()));
    _name->attachTo(_view);
    
    _continue = new Sprite;
    _continue->setResAnim(resources.getResAnim("continue_selected"));
    _continue->setAnchor(Vector2(0.5f, 0.5f));
    _continue->setPosition(Vector2(768 / 2, 768 / 2 - 50));
    _continue->attachTo(_view);
    
    _quit = new Sprite;
    _quit->setResAnim(resources.getResAnim("quit"));
    _quit->setAnchor(Vector2(0.5f, 0.5f));
    _quit->setPosition(Vector2(768 / 2, 768 / 2 + _quit->getHeight() - 50));
    _quit->attachTo(_view);
    
    // Add escape key listener
    Input::instance.addEventListener(Input::event_platform, CLOSURE(this, &PauseMenu::_onEvent));
}

void PauseMenu::setContinue(string continueImage) {
    _continue->setResAnim(resources.getResAnim(continueImage));
}

void PauseMenu::setQuit(string quitImage) {
    _quit->setResAnim(resources.getResAnim(quitImage));
}

/**
 * Keyboard event handler.
 *
 * @ev is the SDL event sent by the event listener.
 */
void PauseMenu::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && _isReady) {
        switch (event->key.keysym.sym) {
            case SDLK_RETURN:
                if (_selection == selectContinue) {
                    _isReady = false;
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
                selectNext();
                break;
            default:
                break;
        }
    }
    
    if (event->type == SDL_KEYUP && event->key.repeat == 0) {
        switch (event->key.keysym.sym) {
            case SDLK_ESCAPE:
                _isReady = true;
                break;
            default:
                break;
        }
    }
}


/**
 * Selects the next item in the menu list.
 */
void PauseMenu::selectNext() {
    if (_selection == selectContinue) {
        _selection = selectQuit;
        setQuit("quit_selected");
        setContinue("continue");
    } else if (_selection == selectQuit) {
        _selection = selectContinue;
        setQuit("quit");
        setContinue("continue_selected");
    }
}
