#pragma once
#include "oxygine-framework.h"

#ifndef __S3E__
#include "SDL.h"
#endif

using namespace oxygine;

class KeyboardInput: public Sprite {
public:
    KeyboardInput();
    
    bool getDirection(Vector2 &dir) const;
    
private:
    void onEvent(Event *ev);
    bool _pressed;
    Vector2 _dir;
};