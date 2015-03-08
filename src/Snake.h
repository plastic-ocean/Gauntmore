#ifndef __gauntmore__Snake__
#define __gauntmore__Snake__

#include "Creature.h"
#include "Thing.h"

using namespace std;

DECLARE_SMART(Snake, spSnake);
class Snake : public Creature {
    
public:
    Snake();
    
    /* Virtual Methods */
    
    virtual SDL_Rect getBounds();
    //virtual void damage();
    virtual void addSprite();
    virtual bool isPotion();
    
    void move();
    
private:

    Facing _facing;
    spThing _contents;
    int _speed = 100;
    spTween _moveTween;
    
    /**
     * Initializes position and sprite of Chest. Called by Unit's init() method.
     */
    void _init();
    
    /**
     * Updates the Chest every frame. Called by Units update() method.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
    void _update(const UpdateState &us);
};

#endif /* defined(__gauntmore__Snake__) */
