#pragma once
#include "Unit.h"
#include "CollisionDetector.h"
#include "res.h"

DECLARE_SMART(Player, spPlayer);
class Player: public Unit {
    
public:
	Player(int hp, int attack, int defense);
    
    enum Facing {up, right, down, left};
    
    /**
     * Get the bounds used for collision detection.
     */
    virtual SDL_Rect getBounds();
    
    /**
     * Get the current facing.
     */
    Facing getFacing();
    
    /**
     * Updates the player's health.
     *
     * @health is the number to add to _hp.
     * @return true if it was updated, false if it was not.
     */
    bool updateHealth(int health);
    
    /**
     * Interacts with Things or Creatures.
     */
    void interact();
    
    /**
     * Plays the attack animation.
     */
    void attack();
    
    /**
     * Plays the move animation.
     *
     * @facing is a int. 0: up, 1: right, 2: down, 3: left
     */
    void move(int facing);
    
    /**
     * Sets the sprite's standing image.
     */
    void stand();
    
    /**
     * Remove the tween from the sprite.
     */
    void removeTween(int facing);
    
    /**
     * Add sprite to the game scene.
     */
    void addSprite();
    
    /**
     * Checks if the player is damaged by comparing _hp to maxHealth.
     */
    bool isDamaged();
    
protected:
    const int tileSize = 64;
    
    Facing _facing;
    spCollisionDetector _collisionDetector;
    
    spTween _moveUpTween;
    spTween _moveRightTween;
    spTween _moveDownTween;
    spTween _moveLeftTween;
    
    spTween _attackTween;
    bool _hasTween;
    bool _isMoving;
    
    /**
     * Initializes the player's position and sprite. Called by Unit::init.
     */
    void _init();
    
    /**
     * Updates the player every frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
    void _update(const UpdateState &us);
    
    /**
     * Checks whether the sprite already has a tween before trying to removing it.
     */
    void _checkTween();
    
    /**
     * Checks for a collision between the players rect and the unit's rect.
     *
     * @rect is an SDL_Rect for the player.
     * @unit is the unit to check against.
     */
    bool _isCollision(SDL_Rect rect, spUnit unit);
    
    /**
     * Corrects the movement direction by checking for collision with wall tiles or other Units and adjusting the
     * direction vector's x and y values.
     *
     * @postion is the player's current position.
     * @directions is the player's current movement direction.
     */
    Vector2 _correctDirection(Vector2 position, Vector2 direction);
};
