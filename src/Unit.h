#pragma once
#include "oxygine-framework.h"

using namespace oxygine;
using namespace std;

class Game;
DECLARE_SMART(Unit, spUnit);
class Unit: public Object {
    
public:
    Unit();
    
    /**
     * Initializes a unit. When initializing any child this is the called method.
     * It calls the overloaded _init method for all children.
     *
     * @pos is the unit's position
     * @game is the game.
     */
    void init(const Vector2 &pos, Game *game);
    
    /**
     *  Attaches the Unit to the game as an Actor.
     */
    void attachUnit();
    
    /**
     *  Detaches the Unit to the game as an Actor.
     */
    void detachUnit();
    
    /**
     * Allows the player to interacts with the unit. Calls the _interact method in all children.
     *  Iterates thru list of units and determines which the player is facing.
     *  Then calls that objects interact method.
     */
    void interact();

    /**
     * Updates all Units. Calls method _update that is is defined in children.
     */
    void update(const UpdateState &us);
    
    
    /* Getters and Setters */

    const Vector2& getPosition();
    
    void setPosition(const Vector2& position);
    
    string getType();
    
    void setType(string type);
    
    const bool isDead();

    int getHp();

    int getAttack();

    int getDefense();
    
    void setLocation(Vector2 location);
    
    Vector2 getLocation();
    
    SDL_Rect getRect();
    
    void setRect(SDL_Rect rect);
    
    /**
     * Checks if the Units is a potion.
     */
    bool isPotion();
    
    
    /* Virtual Methods */
    
    /**
     *  Virtual Method implemented in children.
     */
    virtual SDL_Rect getBounds() = 0;
    
    /**
     * Adds the sprite. Implemented by children.
     */
    virtual void addSprite() = 0;

protected:
    Vector2 _location;
    SDL_Rect _bounds;
    spActor _view;
    spSprite _sprite;
    SDL_Rect _rect;
    
    string _type;
    bool _isPotion;
    
    Game *_game;
    
    /**
     * Stats
     */
    int _maxHealth;
    int _hp;
    int _attack;
    int _defense;
    int _speed;
    int _attackSpeed;
    
    /**
     * Indicates if unit is dead. Set by damage() and retrieved with isDead().
     * Used to remove unit from game's units list.
     */
    bool _dead;
    
    /**
     * Initializes a child of Unit. Called by Unit::init() for all children.
     */
	virtual void _init() {}
    
    /**
     * Interact method of Unit. Called by Unit::init() for all children.
     */
    virtual void _interact() {}
    
    /**
     * Updates a child of Unit every frame. Called by Unit::update() for all children.
     *
     * @us is the UpdateStatus sent by Unit's update method.
     */
	virtual void _update(const UpdateState &us) {}
};