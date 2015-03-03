#include "Input.h"
#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_events.h"

#include "StartMenu.h"
#include "res.h"


spStartMenu StartMenu::instance;


StartMenu::StartMenu():_isReady(false) {
    _name = new Sprite;
    _name->setResAnim(resources.getResAnim("title"));
    _name->setAnchor(Vector2(0.5f, 0.5f));
    _name->setPosition(Vector2(768 / 2, (768 / 2) - _name->getHeight()));
    _name->attachTo(_view);
    
    _newGame = new Sprite;
    _newGame->setResAnim(resources.getResAnim("new_game"));
    _newGame->setAnchor(Vector2(0.5f, 0.5f));
    _newGame->setPosition(Vector2(768 / 2, 768 / 2));
    _newGame->attachTo(_view);
    
//    _continue = new Sprite;
//    _continue->setResAnim(resources.getResAnim("continue"));
//    _continue->setAnchor(Vector2(0.5f, 0.5f));
//    _continue->setPosition(Vector2(768 / 2, 768 / 2));
//    _continue->attachTo(_view);
    
    _quit = new Sprite;
    _quit->setResAnim(resources.getResAnim("quit"));
    _quit->setAnchor(Vector2(0.5f, 0.5f));
    _quit->setPosition(Vector2(768 / 2, 768 / 2 + _quit->getHeight()));
    _quit->attachTo(_view);
    
    // Add escape key listener
    Input::instance.addEventListener(Input::event_platform, CLOSURE(this, &StartMenu::_onEvent));
}

void StartMenu::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && _isReady) {
        switch (event->key.keysym.sym) {
            case SDLK_RETURN:
                _isReady = false;
                changeScene(GameScene::instance);
                break;
            case SDLK_TAB:
                // change selection
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
