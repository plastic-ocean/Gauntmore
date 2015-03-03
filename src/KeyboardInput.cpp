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


/**
 * Sets the movement direction and interactino for the Player on valid keyboard input.
 *
 * @ev is the event, will be turned into an SDL_Event.
 */
void KeyboardInput::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    _pressed = true;
    
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0 && !_game->isPaused()) {
        switch (event->key.keysym.sym) {
            case SDLK_UP:
            case SDLK_w:
                _dir += Vector2(0, -1);
                _game->getPlayer()->move(Player::up);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                _dir += Vector2(0, 1);
                _game->getPlayer()->move(Player::down);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                _dir += Vector2(-1, 0);
                _game->getPlayer()->move(Player::left);
                 break;
            case SDLK_RIGHT:
            case SDLK_d:
                _dir += Vector2(1, 0);
                _game->getPlayer()->move(Player::right);
                break;
            case SDLK_SPACE:
                _game->getPlayer()->interact();
                break;
            case SDLK_RETURN:
                _game->getPlayer()->updateHealth(-1);
                break;
            case SDLK_ESCAPE:
                _game->pauseGame();
                break;
            default:
                break;
        }
    }

    if (event->type == SDL_KEYUP && event->key.repeat == 0 && !_game->isPaused()) {
//        _pressed = false;
        switch (event->key.keysym.sym ) {
            case SDLK_UP:
            case SDLK_w:
                _dir -= Vector2(0, -1);
                _game->getPlayer()->removeTween(Player::up);
                break;
            case SDLK_DOWN:
            case SDLK_s:
                _dir -= Vector2(0, 1);
                _game->getPlayer()->removeTween(Player::down);
                break;
            case SDLK_LEFT:
            case SDLK_a:
                _dir -= Vector2(-1, 0);
                _game->getPlayer()->removeTween(Player::left);
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                _dir -= Vector2(1, 0);
                _game->getPlayer()->removeTween(Player::right);
                break;
            default: break;
        }
    }
    
 
}
