#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

class Game;
DECLARE_SMART(Unit, spUnit);
class Unit: public Object {
    
public:
	Unit();
    
    /**
     * Initializes a unit. When initializing any child this is the called method.
     * It calls the overloaded _init method for all children.
     *
     * @pos is the unit's positon
     * @game is the game.
     */
    void init(const Vector2 &pos, Game *game);
    
    /**
     * Gets the unit's position.
     *
     * @return the unit's position.
     */
    const Vector2&getPosition();

    /**
     * Calls the overloaded _update method in children.
     */
    void update(const UpdateState &us);
    
    /**
     * Check for unit death.
     *
     * @returns true if unit is dead and false if it is not.
     */
    const bool isDead() {return _dead;}
    
    /**
     * Reduces the Unit's hit points.
     */
    virtual void damage(){}

protected:
    // Each Unit has a view that is attached to the game.
    spActor _view;
    
    // A pointer to the game.
    Game *_game;
    
    // Stats
    int _hp;
    int _attack;
    int _defense;
    
    // Indiates if unit is dead. Used to remove unit from game's units list.
    bool _dead;
    
    /**
     * Initializes a child of Unit. Called by Unit::init() for all children.
     */
	virtual void _init(){}
    
    /**
     * Updates a child of Unit every frame. Called by Unit::update() for all children.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
	virtual void _update(const UpdateState &us){}
};