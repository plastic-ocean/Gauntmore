#pragma once
#include "Unit.h"

DECLARE_SMART(Player, spPlayer);
class Player: public Unit {
    
public:
<<<<<<< HEAD
	Player(int hp, int attack, int defense);
    
    // up = 0, right = 1, down = 2, left = 3
    enum Facings {up, right, down, left};
    Facings facing;
    
    Facings getFacing();
=======
	Player();
    enum Facing {up, right, down, left};
    Facing facing;
>>>>>>> origin/stevenOffKeith
    
    int i = 0;

    /**
     * Reduces the player's hit points.
     */
    void damage();
    
    /**
     * Add sprite to the game scene.
     */
    void addSprite();
    
<<<<<<< HEAD
    void attack();
    void attackDown();
    void attackUp();
    void attackLeft();
    void attackRight();
=======
    void interact();
    
    void removeSprite();
>>>>>>> origin/stevenOffKeith
    
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    
    void removeTween();
    
protected:
    const int tileSize = 64;
    spTween _moveTween;
    spTween _attackTween;
    bool _hasTween;
    
    void _checkTween();
    
    Vector2 correctDirection(Vector2 position, Vector2 direction);
    
    /**
     * Initializes the player's position and sprite. Called by Unit's init() method.
     */
	void _init();
    
    void _setFacing(Vector2 dir);

    bool _isExit(Vector2 position);
    
    /**
     * Updates the player every frame.
     *
     * @us is the UpdateStatus sent by the global update method.
     */
	void _update(const UpdateState &us);


};
