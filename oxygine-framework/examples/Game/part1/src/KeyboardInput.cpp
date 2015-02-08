#include "KeyboardInput.h"
#include "Input.h"

#ifndef __S3E__
#include "SDL_keyboard.h"
#include "SDL_events.h"
#endif

KeyboardInput::KeyboardInput():_pressed(false), _dir(0,0) {
    Input::instance.addEventListener(Input::event_platform, CLOSURE(this, &KeyboardInput::onEvent));
}

bool KeyboardInput::getDirection(Vector2 &dir) const {
    dir = _dir;
    return _pressed;
    
}

void KeyboardInput::onEvent(Event *ev) {
    SDL_Event *event = (SDL_Event*) ev->userData;
    
    if (event->type == SDL_KEYDOWN) {
        _pressed = true;
        switch (event->type) {
            case SDLK_UP:
                _dir = Vector2(10, 0);
                break;
            case SDLK_w:
                _dir = Vector2(10, 0);
                break;
            case SDLK_DOWN:
                _dir = Vector2(-10, 0);
                break;
            case SDLK_s:
                _dir = Vector2(-10, 0);
                break;
            case SDLK_LEFT:
                _dir = Vector2(0, -10);
                break;
            case SDLK_a:
                _dir = Vector2(0, -10);
                break;
            case SDLK_RIGHT:
                _dir = Vector2(0, 10);
                break;
            case SDLK_d:
                _dir = Vector2(0, 10);
                break;
        }
    } else if (event->type == SDL_KEYUP) {
        _pressed = false;
    }
    
    if (_dir.length() > 100)
        _dir.normalizeTo(100);
    
    if (!_pressed) {
        _dir = Vector2(0,0);
    }
}

