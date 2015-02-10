#include <iostream>

#include "KeyboardInput.h"
#include "Input.h"
#include "SDL.h"
#include "SDL_keyboard.h"
#include "SDL_events.h"


/**
 * Constructor.
 */
KeyboardInput::KeyboardInput():_pressed(false), _dir(0,0) {
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
 * Sets the movement direction for the Player on valid keyboard input.
 * 
 * @ev is the event, will be turned into an SDL_Event.
 */
/*void KeyboardInput::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    
    if (event->type == SDL_KEYDOWN) {
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        _pressed = true;
        if ((state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) || (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_W])) {
            // Up/Left
            _dir = Vector2(-20, -20);
        } else if ((state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) || (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W])) {
            // Up/Right
            _dir = Vector2(20, -20);
        } else if ((state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT]) || (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])) {
            // Down/Left
            _dir = Vector2(-20, 20);
        } else if ((state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]) || (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])) {
            // Down/Right
            _dir = Vector2(20, 20);
        } else if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
            // Up
            _dir = Vector2(0, -20);
        } else if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
            // Down
            _dir = Vector2(0, 20);
        } else if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
            // Left
            _dir = Vector2(-20, 0);
        } else if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
            // Right
            _dir = Vector2(20, 0);
        }
    } else if (event->type == SDL_KEYUP) {
        _pressed = false;
        _dir = Vector2(0,0);
    }
    
    
}*/

void KeyboardInput::_onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
//    const Uint8 *state = SDL_GetKeyboardState(NULL);
    _pressed = true;
    //if key is pressed:
    if (event->type == SDL_KEYDOWN && event->key.repeat == 0) {
        //adjust velocity
        switch (event->key.keysym.sym ) {
            case SDLK_UP:
            case SDLK_w: _dir += Vector2(0, -1); break;
            
            case SDLK_DOWN:
            case SDLK_s: { //for anim testing
                _dir += Vector2(0, 1);
                
                break;
            }
            case SDLK_LEFT:
            case SDLK_a: _dir += Vector2(-1, 0); break;
            case SDLK_RIGHT:
            case SDLK_d: _dir += Vector2(1, 0); break;
 
        }
    }
        if (event->type == SDL_KEYUP && event->key.repeat == 0) {
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
        }
    }
    
  /*  if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
        // Up
        _dir += Vector2(0, -1);
    }
    if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
        // Up
        _dir += Vector2(0, 1);
    }
    if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
        // Up
        _dir += Vector2(-1, 0);
    }
    if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
        // Up
        _dir += Vector2(1, 0);
    }
    if (event->type == SDL_KEYUP) {
    _pressed = false;
    _dir = Vector2(0,0);
}
*/
}