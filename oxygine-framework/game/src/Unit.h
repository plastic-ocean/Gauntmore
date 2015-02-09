#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

class Game;
DECLARE_SMART(Unit, spUnit);
class Unit: public Object {
    
public:
	Unit();
    
    /**
     * Initializes a unit.
     *
     * @pos is the units positon
     * @game is the game.
     */
    void init(const Vector2 &pos, Game *game);
    
    /**
     * Gets the units potions.
     *
     * @return the unit's position
     */
    const Vector2&getPosition();

    /**
     * Virtual method is overload in children.
     */
    void update(const UpdateState &us);
    
    /**
     * Check for unit death.
     *
     * @returns ture if unit is dead and false if it is not.
     */
    bool isDead() const {return _dead;}

protected:
    spActor _view;
    Game *_game;
    
    int _hp;
    int _attack;
    int _defense;
    bool _dead;
    
    /**
     * Initializes a units position and sprite. Called by the init() method by children.
     */
	virtual void _init(){}
    
    /**
     * Updates the unit every frame. Called by the update() method by children.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
	virtual void _update(const UpdateState &us){}
    
    /**
     * Reduces the creatures hit points.
     */
    virtual void damage(){}
};