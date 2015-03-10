#pragma once

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Slime, spSlime);
class Slime : public Creature {
    
public:
    Slime();
    
    /* Virtual Methods */
    
    /**
     *  Gets bounds of the unit Slime.
     *  @return: SDL_Rect _bounds which is the bounds of Slime.
     */
    virtual SDL_Rect getBounds();
    
    /**
     *  Adds Sprite and attaches it to the game.
     */
    virtual void addSprite();

    
    /**
     * Plays the move animation.
     */
    void move();
    
private:
    Facing _facing;
    spThing _contents;
    spTween _moveTween;
    
    /**
     * Initializes a Slime position and sprite. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Updates the Chest every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

