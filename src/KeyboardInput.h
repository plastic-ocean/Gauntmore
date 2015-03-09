#pragma once
#include "oxygine-framework.h"

using namespace oxygine;

class Game;
class KeyboardInput: public Actor {
    
public:
    KeyboardInput(Game *game);
    
    /**
     * Gets and sets the direction Vector2 on keyboard input. Used by Player to move the sprite..
     *
     * @dir is the direction vector.
     * @return true on a button press and false when it is lifted up.
     */
    bool getDirection(Vector2 &dir) const;

    /**
     * Resets keyboard direction to 0.
     */
    void resetDir();
    
private:
    bool _pressed;
    Vector2 _dir;
    Game *_game;
    
    /**
     * Sets the movement direction and interactino for the Player on valid keyboard input.
     *
     * @ev is the event, will be turned into an SDL_Event.
     */
    void _onEvent(Event *ev);
};