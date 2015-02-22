#pragma once
#include "Unit.h"
#include "CollisionDetector.h"

DECLARE_SMART(Player, spPlayer);
class Player: public Unit {
    
public:
	Player(int hp, int attack, int defense);
    
    enum Facing {up, right, down, left};
    
    Facing getFacing();

    /**
     * Reduces the player's hit points.
     */
    void damage();
    
    /**
     * Add sprite to the game scene.
     */
    void addSprite();
    void removeSprite();
    
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
     */
    void move(int facing);

    void removeTween();
    
    virtual SDL_Rect getBounds();
    
protected:
    Facing _facing;
    
    int i = 0;
    spCollisionDetector _collisionDetector;
    const int tileSize = 64;
    spTween _moveTween;
    spTween _attackTween;
    bool _hasTween;
    
    void _checkTween();
    
    /**
     * Corrects the movement direction by checking for collision with wall tiles or other Units and adjusting the
     * direction vector's x and y values.
     *
     * @postion is the player's current position.
     * @directions is the player's current movement direction.
     */
    Vector2 _correctDirection(Vector2 position, Vector2 direction);
    
    /**
     * Initializes the player's position and sprite. Called by Unit's init() method.
     */
	void _init();
    
    void _setFacing(Vector2 dir);

    bool _isExit(Vector2 position);
    
    bool _isCollision(SDL_Rect rect, spUnit unit);
    
    /**
     * Updates the player every frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void _update(const UpdateState &us);


};
