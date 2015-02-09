#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

#ifndef __S3E__
#include "SDL.h"
#endif

using namespace oxygine;

class KeyboardInput: public Actor {
public:
    KeyboardInput();
    
    /**
     * Gets and sets the direction Vector2 on keyboard input. Used by Player to move the sprite..
     *
     * @dir is the direction vector.
     * @return true on a button press and false when it is lifted up.
     */
    bool getDirection(Vector2 &dir) const;
    
private:
    bool _pressed;
    Vector2 _dir;
    
    /**
     * Sets the movement direction for the Player on valid keyboard input.
     *
     * @ev is the event, will be turned into an SDL_Event.
     */
    void onEvent(Event *ev);
};