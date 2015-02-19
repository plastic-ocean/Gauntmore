#include <iostream>

#include "KeyboardInput.h"
#include "Game.h"
#include "Input.h"
#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_events.h"
#include "Player.h"
#include "Unit.h"
#include "Chest.h"
#include "Gold.h"
#include "Potion.h"

/**
 * Constructor.
 */
KeyboardInput::KeyboardInput(Game *game):_game(game), _pressed(false), _dir(0,0) {
    Input::instance.addEventListener(Input::event_platform, CLOSURE(this, &KeyboardInput::_onEvent));
}


/**
 * Gets and sets the direction Vector2 on keyboard input. Used by Player to move the sprite..
 *
 * @dir is the direction vector.
 * @return true on a button press and false when it is lifted up.
 */
bool KeyboardInput::getDirection(Vector2 &dir) const {
    dir = _dir;
    return _pressed;
    
}


void KeyboardInput::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    _pressed = true;
    // if key is pressed:
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
        // adjust velocity
        switch (event->key.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                _dir += Vector2(0, -1);
                _game->getPlayer()->moveUp();
                break;
            case SDLK_DOWN:
            case SDLK_s:
                // for anim testing
                _dir += Vector2(0, 1);
                _game->getPlayer()->moveDown();
                break;
            case SDLK_LEFT:
            case SDLK_a:
                _dir += Vector2(-1, 0);
                _game->getPlayer()->moveLeft();
                 break;
            case SDLK_RIGHT:
            case SDLK_d:
                _dir += Vector2(1, 0);
                _game->getPlayer()->moveRight();
                break;
<<<<<<< HEAD
            case SDLK_SPACE:
                _game->getPlayer()->attack();
            default:
                break;
=======
            }
            case SDLK_SPACE:
                _game->_chest->interact();
//                _game->_unit->interact();
                 break;
                
//                _game->_chest->interact();
    //            _game->getPlayer()->interact();
               
>>>>>>> origin/stevenOffKeith
        }
    }
    if (event->type == SDL_KEYUP && event->key.repeat == 0) {
        _game->getPlayer()->removeTween();
            //_pressed = false;
        switch (event->key.keysym.sym ) {
            case SDLK_UP:
            case SDLK_w: _dir -= Vector2(0, -1); break;
            case SDLK_DOWN:
            case SDLK_s: _dir -= Vector2(0, 1); break;
            case SDLK_LEFT:
            case SDLK_a: _dir -= Vector2(-1, 0); break;
            case SDLK_RIGHT:
            case SDLK_d: _dir -= Vector2(1, 0); break;
            default: break;
        }
    }
    
 
}
