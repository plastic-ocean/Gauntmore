#include <iostream>

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
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        _pressed = true;
        if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W]) {
            // Up
            _dir = Vector2(0, -20);
        }
        if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S]) {
            // Down
            _dir = Vector2(0, 20);
        }
        if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A]) {
            // Left
            _dir = Vector2(-20, 0);
        }
        if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D]) {
            // Right
            _dir = Vector2(20, 0);
        }
        if ((state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) || (state[SDL_SCANCODE_A] && state[SDL_SCANCODE_W])) {
            // Up/Left
            _dir = Vector2(-20, -20);
        }
        if ((state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) || (state[SDL_SCANCODE_D] && state[SDL_SCANCODE_W])) {
            // Up/Right
            _dir = Vector2(20, -20);
        }
        if ((state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_LEFT]) || (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A])) {
            // Down/Left
            _dir = Vector2(-20, 20);
        }
        if ((state[SDL_SCANCODE_DOWN] && state[SDL_SCANCODE_RIGHT]) || (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D])) {
            // Down/Right
            _dir = Vector2(20, 20);
        }
    } else if (event->type == SDL_KEYUP) {
        _pressed = false;
        _dir = Vector2(0,0);
    }
}

